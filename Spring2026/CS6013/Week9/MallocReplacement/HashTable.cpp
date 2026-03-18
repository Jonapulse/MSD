//
// Created by Jonathan Pulsipher on 3/15/26.
//

#include "HashTable.h"

HashTable::HashTable() {
    size = 0;
    maxSize = INITIAL_CAPACITY;
    table.resize(maxSize, 0);
}

void HashTable::insert(void *key, int value) {

}

void HashTable::remove(void *key, int value) {

}

/**
 * grows the table and rehashes its values
 */
void HashTable::grow() {
    std::vector<int> forRehash;
    for (int i = 0; i < maxSize; i++) {
        if (table[i] > 0)
            forRehash.push_back(table[i]);
    }
    maxSize *= GROW_FACTOR;
    table.resize(maxSize, 0);
    //WAIT! Fuck. How do I rehash? I don't have those keys...
    //collect non-tombstone values
    //remake vector
}

int HashTable::hashFunction(void* key) {
    std::uintptr_t x = reinterpret_cast<std::uintptr_t>(key);
    return x >> 3 % maxSize;
}

int HashTable::find() {

}