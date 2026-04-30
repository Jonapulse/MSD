//
// Created by Jonathan Pulsipher
//

#ifndef MALLOCREPLACEMENT_MYMEMORY_H
#define MALLOCREPLACEMENT_MYMEMORY_H

#include "HashTable.h"
#include <vector>

class MyMalloc {
public:
    void* allocate(size_t bytesToAllocate);
    void deallocate(void* ptr);

    MyMalloc();
    ~MyMalloc();
private:
    HashTable* ptrSizes;
    std::vector<void*> pages;

};

#endif //MALLOCREPLACEMENT_MYMEMORY_H