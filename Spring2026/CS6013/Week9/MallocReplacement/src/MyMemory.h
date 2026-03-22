//
// Created by Jonathan Pulsipher
//

#ifndef MALLOCREPLACEMENT_MYMEMORY_H
#define MALLOCREPLACEMENT_MYMEMORY_H


class MyMemory {
public:
    void* allocate(int bytesToAllocate);
    void deallocate(void* ptr);

    MyMemory();
    ~MyMemory();
};


#endif //MALLOCREPLACEMENT_MYMEMORY_H