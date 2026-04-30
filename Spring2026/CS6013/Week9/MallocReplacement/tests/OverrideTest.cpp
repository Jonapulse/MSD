//////////////////////////////////////////////
// Created by Jonathan Pulsipher on 4/30/2026
// Using generated tests
/////////////////////////////////////////////

#include <gtest/gtest.h>
#include "../src/MyMalloc.h"
#include <cstdlib>

static MyMalloc globalAllocator;
static bool overrideActive = false;

// On macOS, use interpose attribute to hook malloc/free
extern "C" {

    void* test_malloc(size_t size) {
        if (overrideActive)
            return globalAllocator.allocate(size);
        return ::malloc(size);  // calls real malloc via :: scope resolution
    }

    void test_free(void* ptr) {
        if (ptr == nullptr) return;
        if (overrideActive)
            globalAllocator.deallocate(ptr);
        else
            ::free(ptr);
    }

    // macOS dyld interpose — hooks malloc/free at the dynamic linker level
    __attribute__((used)) static struct {
        const void* replacement;
        const void* original;
    } interpose_malloc __attribute__((section("__DATA,__interpose"))) = {
        (const void*)test_malloc,
        (const void*)::malloc
    };

    __attribute__((used)) static struct {
        const void* replacement;
        const void* original;
    } interpose_free __attribute__((section("__DATA,__interpose"))) = {
        (const void*)test_free,
        (const void*)::free
    };

} // extern "C"

TEST(OverrideTest, DropInReplacementWorks) {
    overrideActive = true;
    int* p = (int*)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++)
        p[i] = i;
    for (int i = 0; i < 10; i++)
        EXPECT_EQ(p[i], i);
    free(p);
    overrideActive = false;
}

TEST(OverrideTest, FreeNullptrNoThrow) {
    overrideActive = true;
    EXPECT_NO_THROW(free(nullptr));
    overrideActive = false;
}

TEST(OverrideTest, MultipleAllocationsDoNotOverlap) {
    overrideActive = true;
    const int n = 10;
    void* ptrs[n];
    for (int i = 0; i < n; i++)
        ptrs[i] = malloc(sizeof(int) * 100);
    for (int i = 0; i < n; i++)
        *(int*)ptrs[i] = i * 1000;
    for (int i = 0; i < n; i++)
        EXPECT_EQ(*(int*)ptrs[i], i * 1000)
            << "Overlap detected at allocation " << i;
    for (int i = 0; i < n; i++)
        free(ptrs[i]);
    overrideActive = false;
}