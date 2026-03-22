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
class HashTable {
public:
    HashTable();
    ~HashTable();

    void insert(void* key, int value);
    void remove(void* key); //For chaining
    bool contains(void* key);
    int get(void* key);
    int getSize();

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
    int size;
    int capacity;

    //mmap/mmunmap memory allocation
    HashEntry* allocateTable(int cap);
    void freeTable(void* table, int cap);

    int find(void* key);
    void grow();
    int hashFunction(void* key);
};

#endif //MALLOCREPLACEMENT_HASHTABLE_H