//////////////////////////////////////////////////////////////////////////////////
//
// Jon Pulsipher - 6013, OpenMP Parallel Reductions. April, 2026.
//
//////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <numeric>
#include <tuple>
#include <cassert>
#include <cstdlib>
#include <omp.h>

// ─────────────────────────────────────────────────────────────────────────────
// Return type: holds the computed sum and the elapsed time in seconds.
// ─────────────────────────────────────────────────────────────────────────────
template<typename T>
struct Data {
    T      sum;
    double time_seconds;
};

// ─────────────────────────────────────────────────────────────────────────────
// Helper: wall-clock timestamp using std::chrono
// ─────────────────────────────────────────────────────────────────────────────
using Clock     = std::chrono::high_resolution_clock;
using TimePoint = std::chrono::time_point<Clock>;

static inline double elapsed(TimePoint start, TimePoint end) {
    return std::chrono::duration<double>(end - start).count();
}

// =============================================================================
// PART 1 – STL parallel reduction
//
// Strategy: partial-sums approach.
//   • Divide the array into num_threads contiguous chunks.
//   • Each thread accumulates its chunk into a private partial sum stored in a
//     shared vector (no lock needed – each thread writes to its own slot).
//   • The main thread adds the partial sums after all threads join (no lock,
//     no atomic needed for the final reduction).
//
//   No data races arise because:
//     - partial[i] is written only by thread i.
//     - The join() guarantees all writes are visible before the main thread
//       reads the vector.
// =============================================================================
template<typename T>
Data<T> parallel_sum_std(T a[], size_t N, size_t num_threads) {

    // Clamp thread count to array size to avoid empty-range edge cases.
    num_threads = std::min(num_threads, N == 0 ? (size_t)1 : N);

    std::vector<T>          partial(num_threads, T{0});
    std::vector<std::thread> workers;
    workers.reserve(num_threads);

    auto t_start = Clock::now();

    // Launch threads
    for (size_t tid = 0; tid < num_threads; ++tid) {
        // Compute the slice [begin, end) for this thread
        size_t begin = tid       * N / num_threads;
        size_t end   = (tid + 1) * N / num_threads;

        workers.emplace_back([&partial, a, begin, end, tid]() {
            T local{0};
            for (size_t i = begin; i < end; ++i)
                local += a[i];
            partial[tid] = local;       // no race: each thread owns its slot
        });
    }

    // Wait for all threads
    for (auto& t : workers) t.join();

    // Master thread sums the partial results
    T total{0};
    for (auto& p : partial) total += p;

    auto t_end = Clock::now();

    return { total, elapsed(t_start, t_end) };
}

// =============================================================================
// PART 2 – OpenMP manual reduction
//
// Mirrors the STL approach: each OpenMP thread writes its partial sum to a
// private slot, then the master reduces after the parallel region closes.
// We deliberately avoid the 'reduction' clause to build the logic by hand.
// =============================================================================
template<typename T>
Data<T> parallel_sum_omp1(T a[], size_t N, size_t num_threads) {

    // Clamp
    int nthreads = static_cast<int>(std::min(num_threads,
                                             N == 0 ? (size_t)1 : N));

    std::vector<T> partial(nthreads, T{0});

    double t_start = omp_get_wtime();

    #pragma omp parallel num_threads(nthreads)
    {
        int    tid   = omp_get_thread_num();
        int    total = omp_get_num_threads();
        size_t begin = static_cast<size_t>(tid)     * N / total;
        size_t end   = static_cast<size_t>(tid + 1) * N / total;

        T local{0};
        for (size_t i = begin; i < end; ++i)
            local += a[i];

        partial[tid] = local;   // no race: each thread writes its own slot
    } // implicit barrier – all threads done before we proceed

    T sum{0};
    for (auto& p : partial) sum += p;

    double t_end = omp_get_wtime();

    return { sum, t_end - t_start };
}

// =============================================================================
// PART 3 – OpenMP built-in reduction
//
// Uses the 'reduction(+:sum)' clause.  OpenMP generates private copies of
// 'sum', initialised to the identity (0 for addition), and combines them
// automatically at the end of the parallel region.
// =============================================================================
template<typename T>
Data<T> parallel_sum_omp_builtin(T a[], size_t N, size_t num_threads) {

    int nthreads = static_cast<int>(std::min(num_threads,
                                             N == 0 ? (size_t)1 : N));
    T sum{0};

    double t_start = omp_get_wtime();

    #pragma omp parallel for num_threads(nthreads) reduction(+:sum)
    for (size_t i = 0; i < N; ++i)
        sum += a[i];

    double t_end = omp_get_wtime();

    return { sum, t_end - t_start };
}

// =============================================================================
// PART 4 – Testing: correctness + timing
// =============================================================================
int main() {
    // ── Build a test array ───────────────────────────────────────────────────
    constexpr size_t N = 100'000'000;   // 100 M doubles ~800 MB
    std::vector<double> a(N);

    // Fill with 1.0 so the correct sum is exactly N
    std::fill(a.begin(), a.end(), 1.0);

    const double EXPECTED = static_cast<double>(N);

    // Thread counts to benchmark
    std::vector<size_t> thread_counts = {1, 2, 4, 8};

    // ── Header ───────────────────────────────────────────────────────────────
    std::cout << "\n=== Parallel Reduction Benchmark ===\n";
    std::cout << "Array size : " << N << " doubles\n";
    std::cout << "Expected   : " << EXPECTED << "\n\n";

    auto check = [&](const char* label, double sum) {
        bool ok = (sum == EXPECTED);
        std::cout << (ok ? "  [PASS]" : "  [FAIL]");
        if (!ok) std::cout << " (got " << sum << " expected " << EXPECTED << ")";
        (void)label;
    };

    // ── Run benchmarks ────────────────────────────────────────────────────────
    printf("%-28s  %8s  %12s  %s\n",
           "Method", "Threads", "Time (ms)", "Status");
    printf("%-28s  %8s  %12s  %s\n",
           "------", "-------", "---------", "------");

    for (size_t nt : thread_counts) {

        // Part 1: STL threads
        {
            auto [sum, t] = parallel_sum_std(a.data(), N, nt);
            printf("%-28s  %8zu  %12.3f", "STL (partial sums)", nt, t * 1000.0);
            check("STL", sum);
            printf("\n");
        }

        // Part 2: OpenMP manual
        {
            auto [sum, t] = parallel_sum_omp1(a.data(), N, nt);
            printf("%-28s  %8zu  %12.3f", "OpenMP (manual partial)", nt, t * 1000.0);
            check("OMP1", sum);
            printf("\n");
        }

        // Part 3: OpenMP built-in reduction
        {
            auto [sum, t] = parallel_sum_omp_builtin(a.data(), N, nt);
            printf("%-28s  %8zu  %12.3f", "OpenMP (builtin reduction)", nt, t * 1000.0);
            check("OMP_builtin", sum);
            printf("\n");
        }

        printf("\n");
    }

    return 0;
}
