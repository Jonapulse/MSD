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
    ~HashTable();

    //Maps pointers to their size
    void insert(void* key, int value);
    void remove(void* key, int value); //For chaining

private:
    static constexpr int INITIAL_CAPACITY = 16;
    static constexpr float RESIZE_FRACTION = 0.75f;
    static constexpr float GROW_FACTOR = 2;
    static constexpr int TOMBSTONE = -1;

    std::vector<int> table;
    int size;
    int maxSize;
    void grow();
    int hashFunction(void* key);
    int find();
};

#endif //MALLOCREPLACEMENT_HASHTABLE_H