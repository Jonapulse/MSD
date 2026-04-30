//////////////////////////////////////////
// Created by Jonathan Pulsipher - 3/22/26
//////////////////////////////////////////

#include "MyMalloc.h"
#include <stdexcept>
#include <sys/mman.h>
#include <unistd.h>

MyMalloc::MyMalloc() {
    ptrSizes = new HashTable();
}

MyMalloc::~MyMalloc() {
    delete ptrSizes;
}

static size_t roundUpToPageSize(size_t bytes) {
    size_t pageSize = getpagesize();
    return (bytes + pageSize - 1) & ~(pageSize - 1);
}

void* MyMalloc::allocate(size_t bytesToAllocate) {
    size_t rounded = roundUpToPageSize(bytesToAllocate);
    void* ptr = mmap(nullptr, bytesToAllocate, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (ptr == MAP_FAILED)
        throw std::runtime_error("mmap failed");
    ptrSizes->insert(ptr, rounded);
    return ptr;
}

void MyMalloc::deallocate(void* ptr) {
    size_t size = ptrSizes->get(ptr);
    ptrSizes->remove(ptr);
    munmap(ptr, size);
}
