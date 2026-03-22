//////////////////////////////////////////
// Created by Jonathan Pulsipher 3/15/26
// This is a Linear-probing hash table
//////////////////////////////////////////

#ifndef MALLOCREPLACEMENT_HASHTABLE_H
#define MALLOCREPLACEMENT_HASHTABLE_H

#include <vector>

class HashTable {
public:
    HashTable();

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

    static constexpr int INITIAL_CAPACITY = 16;
    static constexpr float RESIZE_FRACTION = 0.75f;
    static constexpr float GROW_FACTOR = 2;

    std::vector<HashEntry> table;
    int size;
    int capacity;

    void grow();
    int hashFunction(void* key);
    int find(void* key);
};

#endif //MALLOCREPLACEMENT_HASHTABLE_H