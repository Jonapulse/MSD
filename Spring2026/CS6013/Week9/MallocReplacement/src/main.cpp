#include <iostream>
#include "MyMalloc.h"
#include <chrono>

int runTimingTest(int type, bool useMyMalloc);
void testManySmall(int n, bool useMyMalloc);
void testManyBig(int n, int size, bool useMyMalloc);
void testManyMixed(int n, int size, bool useMyMalloc);
void testMin(bool useMyMalloc);
constexpr int TEST_N = 100000;
constexpr int TEST_SIZE = 10000;

int main(int argc, char** args){

    //Running/discarding a 'dummy' test because 1st test has overhead I don't want in data
    runTimingTest(1, true);

    int myMallocSmall = runTimingTest(0, true);
    int baseSmall = runTimingTest(0, false);
    int myMallocBig = runTimingTest(1, true);
    int baseBig = runTimingTest(1, false);
    int myMallocMixed = runTimingTest(2, true);
    int baseMixed = runTimingTest(2, false);
    int myMallocMin = runTimingTest(3, true);
    int baseMin = runTimingTest(3, false);
    std::cout << "Comparing timing of MyMalloc vs malloc/free\nFor "
        << TEST_N << " small values:\n\t"
        <<"MyMalloc: " << myMallocSmall << "ms\n\tmalloc: " << baseSmall << "ms\n"
        << "For " << TEST_N << " values of size " << TEST_SIZE << ":\n\t"
        <<"MyMalloc: " << myMallocBig << "ms\n\tmalloc: " << baseBig << "ms\n"
        << "For " << TEST_N << " mixed values of size " << TEST_SIZE << " and ints:\n\t"
        <<"MyMalloc: " << myMallocMixed << "ms\n\tmalloc: " << baseMixed << "ms\n"
        << "For 1 int:\n\t"
        <<"MyMalloc: " << myMallocMin << " microseconds\n\tmalloc: " << baseMin << " microseconds\n";

}

/**
 * Timing test wrapper
 * @param type - 0: small, 1: big, 2: mixed, 3: minimum
 * @param useMyMalloc
 * @return duration in milliseconds (special case 3 returns microseconds)
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
        case(3):
            testMin(useMyMalloc);
            break;
    }
    auto end = std::chrono::high_resolution_clock::now();
    if (type == 3) //Special case for 3, which needs microsecond resolution
        return(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
    else
        return(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
}

/**
 * Allocates, assigns, checks, and deallocates n ints.
 * @param n
 * @param useMyMalloc
 */
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

/**
 * Allocates, assigns, checks, and deallocates n variables of size 'size'
 * @param n
 * @param size
 * @param useMyMalloc
 */
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
 * Alternates between large allocations and int while allocating, assigning,
 * checking, and deallocating.
*  @param n
 * @param size
 * @param useMyMalloc
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

/**
 * minimum do-anything test
 * @param useMyMalloc
 */
void testMin(bool useMyMalloc) {

    int* num;
    if (useMyMalloc) {
        MyMalloc memoryManager;
        num = (int*)memoryManager.allocate(sizeof(int));
        *num = 3;
        if (*num != 3)
            throw std::runtime_error("variable did not keep assigned value: " + std::to_string(*num));
        memoryManager.deallocate(num);
    }
    else {
        num = (int*)malloc(sizeof(int));
        *num = 3;
        if (*num != 3)
            throw std::runtime_error("variable did not keep assigned value: " + std::to_string(*num));
        free(num);
    }
}
