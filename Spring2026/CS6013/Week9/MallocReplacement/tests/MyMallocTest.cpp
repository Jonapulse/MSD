//////////////////////////////////////////////
// Created by Jonathan Pulsipher on 3/22/2026.
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