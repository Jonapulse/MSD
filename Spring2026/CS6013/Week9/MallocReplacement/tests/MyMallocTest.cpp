//////////////////////////////////////////////
// Created by Jonathan Pulsipher on 3/22/2026
// Updated with non-overlap generated tests 4/30/2026
/////////////////////////////////////////////

#include <gtest/gtest.h>
#include "../src/MyMalloc.h"

// ─── Basic Operations ────────────────────────────────────────────────────────

TEST(MyMallocTest, SimpleUse) {
    MyMalloc memoryManager = MyMalloc();
    int* num = (int*)memoryManager.allocate(sizeof(int));
    *num = 5;
    EXPECT_EQ(*num, 5);
}

TEST(MyMallocTest, LargeUse) {
    MyMalloc memoryManager;
    int* num = (int*)memoryManager.allocate(sizeof(int) * 10000);
    for (int i = 0; i < 10000; i++)
        num[i] = i;
    for (int i = 0; i < 10000; i++)
        EXPECT_EQ(num[i], i);
    memoryManager.deallocate(num);
}

TEST(MyMallocTest, MultipleCycles) {
    MyMalloc memoryManager;
    for (int i = 0; i < 10; i++) {
        int* ptr = (int*)memoryManager.allocate(sizeof(int) * 100);
        for (int j = 0; j < 100; j++)
            ptr[j] = j;
        EXPECT_EQ(ptr[99], 99);
        memoryManager.deallocate(ptr);
    }
}

TEST(MyMallocTest, LargeUseAndMunmap) {
    MyMalloc memoryManager = MyMalloc();
    int* num = (int*)memoryManager.allocate(sizeof(int) * 10000);
    for (int i = 0; i < 10000; i++)
        num[i] = i;
    memoryManager.deallocate(num);
}

TEST(MyMallocTest, AllocationsDoNotOverlap) {
    MyMalloc memoryManager;
    const int n = 10;
    void* ptrs[n];
    // Allocate n separate regions
    for (int i = 0; i < n; i++)
        ptrs[i] = memoryManager.allocate(sizeof(int) * 100);

    // Write a unique sentinel to each region
    for (int i = 0; i < n; i++)
        *(int*)ptrs[i] = i * 1000;

    // Verify no allocation overwrote another's sentinel
    for (int i = 0; i < n; i++)
        EXPECT_EQ(*(int*)ptrs[i], i * 1000)
            << "Overlap detected at allocation " << i;

    for (int i = 0; i < n; i++)
        memoryManager.deallocate(ptrs[i]);
}