//
// Created by Jonathan Pulsipher
//

#ifndef MALLOCREPLACEMENT_MYMEMORY_H
#define MALLOCREPLACEMENT_MYMEMORY_H

#include "HashTable.h"
#include <vector>

class MyMalloc {
public:
    void* allocate(int bytesToAllocate);
    void deallocate(void* ptr);

    MyMalloc();
    ~MyMalloc();
private:
    HashTable* ptrSizes;
    std::vector<void*> pages;

};

#endif //MALLOCREPLACEMENT_MYMEMORY_H