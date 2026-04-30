///////////////////////////////////
// CS 6013 OpenMP Reductions
// Created by Jonathan Pulsipher on 4/26/26
//
// Three implementations of multi-threaded array summing and timing
// 1. "Simple" approach computing partial sums in parallel while master adds together
// 2. OpenMP Custom Parallel Reduction
// 3. OpenMP built-in reduction
//
// Building with:
// clang++ -std=c++17 -O2 -Xpreprocessor -fopenmp -I$(brew --prefix libomp)/include -L$(brew --prefix libomp)/lib -lomp -o parallel_sum parallel_sum.cpp
//
///////////////////////////////////

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <iomanip>
#include <omp.h>

template<typename T>
struct Data {
    T sum;
    double time;
};

//Utility Clock helpers
using Clock     = std::chrono::high_resolution_clock;
using TimePoint = std::chrono::time_point<Clock>;

static inline double elapsed(TimePoint start, TimePoint end) {
    return std::chrono::duration<double>(end - start).count();
}

/**
 * Computing sums in separate portions while master adds them together.
* @tparam T type compatible with summing
 * @param a array to sum
 * @param N array size
 * @param num_threads number of threads
 * @return Data{ sum, time_slaped}
 */
template<typename T>
Data<T> parallel_sum_std( T a[], size_t N, size_t num_threads ) {

    std::vector<T> thread_portions(num_threads, T{0});
    std::vector<std::thread> threads;
    threads.reserve(num_threads);

    auto start = Clock::now();

    for (size_t t_i = 0; t_i < num_threads; ++t_i) {
        size_t begin = t_i * N / num_threads;
        size_t end = (t_i + 1) * N / num_threads;

        threads.emplace_back([&thread_portions, a, begin, end, t_i]() {
            T local = 0;
            for (size_t i = begin; i < end; ++i)
                local += a[i];
            thread_portions[t_i] = local;
        });
    }

    for (std::thread& thread : threads) {
        thread.join();
    }

    T total = 0;
    for (size_t t_i = 0; t_i < num_threads; ++t_i)
        total += thread_portions[t_i];

    auto end = Clock::now();

    return {total, elapsed(start, end)};
}

/**
 * OpenMP Custom Parallel Reduction
 * @tparam T type compatible with summing
 * @param a array to sum
 * @param N array size
 * @param num_threads number of threads
 * @return Data{ sum, time_elapsed}
 */
template<typename T>
Data<T> parallel_sum_custom_omp( T a[], size_t N, size_t num_threads ) {

    std::vector<T> thread_portions(num_threads, T{0});

    double start = omp_get_wtime();

    #pragma omp parallel num_threads(num_threads)
    {
        int tid = omp_get_thread_num();
        int total = omp_get_num_threads();
        size_t begin = static_cast<size_t>(tid) * N / total;
        size_t end = static_cast<size_t>(tid + 1) * N / total;

        T local = 0;
        for (size_t i = begin; i < end; ++i)
            local += a[i];

        thread_portions[tid] = local;
    }

    T sum = 0;
    for (size_t t_i = 0; t_i < num_threads; ++t_i)
        sum += thread_portions[t_i];

    double end = omp_get_wtime();

    return {sum, end - start};
}

/**
 * OpenMP Built-in Reduction
 * @tparam T type compatible with summing
 * @param a array to sum
 * @param N array size
 * @param num_threads number of threads
 * @return Data{ sum, time_elapsed }
 */
template<typename T>
Data<T> parallel_sum_builtin_omp( T a[], size_t N, size_t num_threads ) {

    T sum = 0;

    double start = omp_get_wtime();

    #pragma omp parallel for num_threads(num_threads) reduction(+:sum)
    for (size_t i = 0; i < N; ++i)
        sum += a[i];

    double end = omp_get_wtime();

    return {sum, end - start};
}

/**
 * Runs timing tests
 * -------
 * Strong Scaling test -
 * As threads increase, does time speed up proportionally?
 * -------
 * Weak Scaling test -
 * As N and threads increase, does time remain constant?
 *
 * To test other types swap the one line marked SWAP HERE.
 * Note: for float/double the check lambda should use a tolerance instead of ==
 * Note: Generated test and print code with guidance
 */
int main() {

    // ── SWAP HERE to test long / float / double ───────────────────────────
    using num_t = int;                          // SWAP: long, float, double
    // ─────────────────────────────────────────────────────────────────────

    const num_t FILL_VALUE  = static_cast<num_t>(1);
    constexpr size_t REPS   = 10;          // repetitions averaged per cell
    constexpr size_t MAX_N  = 4'096'000;

    std::vector<num_t> a(MAX_N, FILL_VALUE);

    std::vector<size_t> test_Ns       = {64000, 256000, 512000, 1024000, 2048000};
    std::vector<size_t> thread_counts = {1, 2, 4, 8, 16};

    // Correctness: expected sum = N * FILL_VALUE (exact for int/long)
    auto check = [&](long long sum, size_t N) -> std::string {
        long long expected = static_cast<long long>(N) *
                             static_cast<long long>(FILL_VALUE);
        return (sum == expected) ? "PASS" : "FAIL";
    };

    // bench(): runs fn REPS times, returns {avg_time_ms, "PASS"/"FAIL"}.
    // Any single rep failing correctness marks the whole cell FAIL.
    auto bench = [&](auto fn, size_t N, size_t nt) -> std::pair<double, std::string> {
        double total_time = 0.0;
        std::string status = "PASS";
        for (size_t r = 0; r < REPS; ++r) {
            auto result = fn(a.data(), N, nt);
            total_time += result.time;
            if (check(static_cast<long long>(result.sum), N) != "PASS")
                status = "FAIL";
        }
        return { (total_time / REPS) * 1000.0, status };
    };

    // Lambdas wrapping each function so bench() can call them uniformly
    auto fn_std  = [](num_t* arr, size_t n, size_t t){ return parallel_sum_std(arr, n, t); };
    auto fn_omp1 = [](num_t* arr, size_t n, size_t t){ return parallel_sum_custom_omp(arr, n, t); };
    auto fn_blt  = [](num_t* arr, size_t n, size_t t){ return parallel_sum_builtin_omp(arr, n, t); };

    auto print_header = []() {
        std::cout << std::setw(10) << "N"
                  << std::setw(10) << "Threads"
                  << std::setw(18) << "Avg Time (ms)"
                  << std::setw(8)  << "Check" << "\n";
    };

    auto print_row = [](size_t N, size_t nt, double avg_ms, const std::string& status) {
        std::cout << std::setw(10) << N
                  << std::setw(10) << nt
                  << std::setw(18) << std::fixed << std::setprecision(3) << avg_ms
                  << std::setw(8)  << status << "\n";
    };

    // =========================================================================
    // 1. STRONG SCALING — fixed N, increasing threads
    // =========================================================================
    std::cout << "\n"
              << "=======================================================\n"
              << "  STRONG SCALING  (fixed N, increasing threads)\n"
              << "  Avg of " << REPS << " runs per cell\n"
              << "=======================================================\n";

    std::cout << "\n--- STL (partial sums) ---\n";
    print_header();
    for (size_t N : test_Ns) {
        for (size_t nt : thread_counts) {
            auto [avg_ms, status] = bench(fn_std, N, nt);
            print_row(N, nt, avg_ms, status);
        }
        std::cout << "\n";
    }

    std::cout << "--- OpenMP (manual partial) ---\n";
    print_header();
    for (size_t N : test_Ns) {
        for (size_t nt : thread_counts) {
            auto [avg_ms, status] = bench(fn_omp1, N, nt);
            print_row(N, nt, avg_ms, status);
        }
        std::cout << "\n";
    }

    std::cout << "--- OpenMP (builtin reduction) ---\n";
    print_header();
    for (size_t N : test_Ns) {
        for (size_t nt : thread_counts) {
            auto [avg_ms, status] = bench(fn_blt, N, nt);
            print_row(N, nt, avg_ms, status);
        }
        std::cout << "\n";
    }

    // =========================================================================
    // 2. WEAK SCALING — N and threads grow together (base_N elements per thread)
    // =========================================================================
    constexpr size_t BASE_N = 64000;

    std::cout << "=======================================================\n"
              << "  WEAK SCALING  (N and threads grow together)\n"
              << "  Each thread always processes base_N = " << BASE_N << " elements\n"
              << "  Avg of " << REPS << " runs per cell\n"
              << "=======================================================\n\n";

    std::cout << std::setw(10) << "N"
              << std::setw(10) << "Threads"
              << std::setw(22) << "STL avg (ms)"
              << std::setw(24) << "OMP Manual avg (ms)"
              << std::setw(26) << "OMP Builtin avg (ms)" << "\n";

    for (size_t nt : thread_counts) {
        size_t N = BASE_N * nt;

        auto [std_ms,  std_ok]  = bench(fn_std,  N, nt);
        auto [omp1_ms, omp1_ok] = bench(fn_omp1, N, nt);
        auto [blt_ms,  blt_ok]  = bench(fn_blt,  N, nt);

        std::cout << std::setw(10) << N
                  << std::setw(10) << nt
                  << std::setw(16) << std::fixed << std::setprecision(3) << std_ms
                  << " (" << std_ok  << ")"
                  << std::setw(16) << omp1_ms
                  << " (" << omp1_ok << ")"
                  << std::setw(16) << blt_ms
                  << " (" << blt_ok  << ")"
                  << "\n";
    }

    std::cout << "\nDone.\n";
    return 0;
}
