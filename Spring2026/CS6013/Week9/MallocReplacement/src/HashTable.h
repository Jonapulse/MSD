//////////////////////////////////////////
// Created by Jonathan Pulsipher 3/15/26
// This is a Linear-probing hash table
//////////////////////////////////////////

#ifndef MALLOCREPLACEMENT_HASHTABLE_H
#define MALLOCREPLACEMENT_HASHTABLE_H

/**
 * HashTable is a custom HashTable for use by MyMalloc
 * It handles its own memory allocation and deallocation
 * through mmap/mmunmap
 */
#include <unistd.h>

class HashTable {
public:
    HashTable();
    ~HashTable();

    void insert(void* key, int value);
    void remove(void* key); //For chaining
    bool contains(void* key);
    int get(void* key);
    size_t getSize();

private:
    struct HashEntry {
        void* key;
        int value;
        bool tombstone;
        bool empty;
    };

    static constexpr int INITIAL_CAPACITY = 4096 / sizeof(HashEntry); //Hash-entries per memory page
    static constexpr float RESIZE_FRACTION = 0.75f;
    static constexpr float GROW_FACTOR = 2;

    HashEntry* table;
    size_t size;
    int capacity;

    //mmap/mmunmap memory allocation
    HashEntry* allocateTable(size_t byte_size);
    void freeTable(void* table, size_t byte_size);

    int find(void* key);
    void grow();
    int hashFunction(void* key);
};

#endif //MALLOCREPLACEMENT_HASHTABLE_H