#include <iostream>
#include "MyMalloc.h"
#include <chrono>

int runTimingTest(int type, bool useMyMalloc);
void testManySmall(int n, bool useMyMalloc);
void testManyBig(int n, int size, bool useMyMalloc);
void testManyMixed(int n, int size, bool useMyMalloc);
constexpr int TEST_N = 100000;
constexpr int TEST_SIZE = 10000;

int main(int argc, char** args){
    int myMallocSmall = runTimingTest(0, true);
    int baseSmall = runTimingTest(0, false);
    int myMallocBig = runTimingTest(1, true);
    int baseBig = runTimingTest(1, false);
    int myMallocMixed = runTimingTest(2, true);
    int baseMixed = runTimingTest(2, false);
    std::cout << "Comparing timing of MyMalloc vs malloc/free\nFor "
        << TEST_N << " small values:\n\t"
        <<"MyMalloc: " << myMallocSmall << "ms\n\tmalloc: " << baseSmall << "ms\n"
        << "For " << TEST_N << " values of size " << TEST_SIZE << ":\n\t"
        <<"MyMalloc: " << myMallocBig << "ms\n\tmalloc: " << baseBig << "ms\n"
        << "For " << TEST_N << " mixed values of size " << TEST_SIZE << " and ints:\n\t"
        <<"MyMalloc: " << myMallocMixed << "ms\n\tmalloc: " << baseMixed << "ms\n";

}

/**
 * Timing test utility function
 * @param type - 0: small, 1: big, 2: mixed
 * @param useMyMalloc
 * @return duration in milliseconds
 */
int runTimingTest(int type, bool useMyMalloc) {
    auto start = std::chrono::high_resolution_clock::now();
    switch (type) {
        case(0):
            testManySmall(TEST_N, useMyMalloc);
            break;
        case(1):
            testManyBig(TEST_N, TEST_SIZE, useMyMalloc);
            break;
        case(2):
            testManyMixed(TEST_N, TEST_SIZE, useMyMalloc);
            break;
    }
    auto end = std::chrono::high_resolution_clock::now();
    return(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
}

void testManySmall(int n, bool useMyMalloc) {
    MyMalloc memoryManager;
    int** smallList;
    if (useMyMalloc)
        smallList = (int**)memoryManager.allocate(sizeof(int*) * n);
    else
        smallList = (int**)malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++) {
        if (useMyMalloc)
            smallList[i] = (int*)memoryManager.allocate(sizeof(int));
        else
            smallList[i] = (int*)malloc(sizeof(int));
        *smallList[i] = i;
    }
    for (int i = 0; i < n; i++) {
        if (*smallList[i] != i)
            throw std::runtime_error("index " + std::to_string(i) + "does not have expected value");
        if (useMyMalloc)
            memoryManager.deallocate(smallList[i]);
        else
            free(smallList[i]);
    }
    if (useMyMalloc)
        memoryManager.deallocate(smallList);
    else
        free(smallList);
}

void testManyBig(int n, int size, bool useMyMalloc){
    MyMalloc memoryManager;
    void** bigList;
    if (useMyMalloc)
        bigList = (void**)memoryManager.allocate(sizeof(void*) * n);
    else
        bigList = (void**)malloc(sizeof(void*) * n);

    for (int i = 0; i < n; i++) {
        if (useMyMalloc)
            bigList[i] = memoryManager.allocate(size);
        else
            bigList[i] = malloc(size);
        *(int*)bigList[i] = i;
    }

    for (int i = 0; i < n; i++) {
        if (*(int*)bigList[i] != i)
            throw std::runtime_error("index " + std::to_string(i) + "does not have expected value");
        if (useMyMalloc)
            memoryManager.deallocate(bigList[i]);
        else
            free(bigList[i]);
    }
    if (useMyMalloc)
        memoryManager.deallocate(bigList);
    else
        free(bigList);
}

/**
 * Alternates between large allocations and int. For setting and
 * checking values, casts both to int.
 */
void testManyMixed(int n, int size, bool useMyMalloc) {
    MyMalloc memoryManager;
    void** bigList;
    if (useMyMalloc)
        bigList = (void**)memoryManager.allocate(sizeof(void*) * n);
    else
        bigList = (void**)malloc(sizeof(void*) * n);

    for (int i = 0; i < n; i++) {
        if (useMyMalloc)
            bigList[i] = i % 2 == 0 ? memoryManager.allocate(size) : memoryManager.allocate(sizeof(int));
        else
            bigList[i] = i % 2 == 0 ? malloc(size) : malloc(sizeof(int));
        *(int*)bigList[i] = i;
    }

    for (int i = 0; i < n; i++) {
        if (*(int*)bigList[i] != i)
            throw std::runtime_error("index " + std::to_string(i) + "does not have expected value");
        if (useMyMalloc)
            memoryManager.deallocate(bigList[i]);
        else
            free(bigList[i]);
    }
    if (useMyMalloc)
        memoryManager.deallocate(bigList);
    else
        free(bigList);
}
