//////////////////////////////////////////
// Created by Jonathan Pulsipher - 3/22/26
//////////////////////////////////////////

#include "MyMalloc.h"

#include <stdexcept>
#include <sys/mman.h>

MyMalloc::MyMalloc() {
    ptrSizes = new HashTable();
}

MyMalloc::~MyMalloc() {
    delete ptrSizes;
}

void* MyMalloc::allocate(int bytesToAllocate) {
    //Do checking
    void* ptr = mmap(nullptr, bytesToAllocate, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (ptr == MAP_FAILED)
        throw std::runtime_error("mmap failed");
    ptrSizes->insert(ptr, bytesToAllocate);
    return ptr;
}
