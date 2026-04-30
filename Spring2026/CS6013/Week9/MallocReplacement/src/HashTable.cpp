//////////////////////////////////////////
// Created by Jonathan Pulsipher 3/15/26
// Implementation of a Linear-probing hash table
//////////////////////////////////////////

#include "HashTable.h"

#include <iostream>
#include <ostream>
#include <stdexcept>
#include <sys/mman.h>

HashTable::HashTable() {
    size = 0;
    capacity = INITIAL_CAPACITY;
    table = allocateTable(capacity);
}

HashTable::~HashTable() {
    freeTable(table, capacity);
}


void HashTable::insert(void *key, int value) {
    if ((float)(size + 1) / capacity > RESIZE_FRACTION)
        grow();

    int index = hashFunction(key);
    int startIndex = index;
    while (!table[index].empty && !table[index].tombstone) {
        if (table[index].key == key) {
            table[index].value = value;
            return;
        }
        index++;
        if (index >= capacity)
            index = 0;
        else if (index == startIndex)
            throw std::runtime_error("Error: attempting add to full HashTable");
    }
    table[index] = {key, value, false, false};
    size++;
}

void HashTable::remove(void *key) {
    int index = find(key);
    if (index == -1)
        return;
    table[index].tombstone = true;
    table[index].empty = false;
    size--;
}

bool HashTable::contains(void* key) {
    return find(key) != -1;
}

int HashTable::get(void* key) {
    int index = find(key);
    if (index == -1)
        throw std::runtime_error("Key not found");
    return table[index].value;
}

/**
 * Creates a table in memory using mmap.
 * REHASHING HANDLED IN GROW
 * @param cap - size (# of HashEntries)
 * @return ptr to table
 */
HashTable::HashEntry* HashTable::allocateTable(size_t byte_size) {
    HashTable::HashEntry* ptr = (HashTable::HashEntry*) mmap(
        nullptr, sizeof(HashEntry) * byte_size,
        PROT_READ | PROT_WRITE,
        MAP_PRIVATE | MAP_ANONYMOUS,
        -1, 0);
    if (ptr == MAP_FAILED)
        throw std::runtime_error("mmap failed");
    for (int i = 0; i < byte_size; i++) {
        ptr[i] = {nullptr, 0, false, true};
    }
    return ptr;
}

/**
* ASSIGNMENT QUESTION: What is a lazy delete from a hash table?
 * When we delete entries we set their tombstone flag to 'true' but do not
 * overwrite any data. This is lazy deletion - data's still there but ignored
 * by the hashtable. It will not copy over on rehash.
 * @param ptr
 */
void HashTable::freeTable(void* ptr, size_t byte_size) {
    munmap(ptr, byte_size);
}

int HashTable::find(void* key) {
    int index = hashFunction(key);
    int startIndex = index;
    while (!table[index].empty) {
        if (!table[index].tombstone && table[index].key == key)
            return index;
        index++;
        if (index >= capacity)
            index = 0;
        if (index == startIndex)
            break;
    }
    return -1;
}

/**
 * grows the table and rehashes its values
 */
void HashTable::grow() {
    HashEntry* oldTable = table;
    int oldCapacity = capacity;
    capacity *= GROW_FACTOR;
    table = allocateTable(capacity);
    size = 0;
    for (int i = 0; i < oldCapacity; i++) {
        if (!oldTable[i].empty && !oldTable[i].tombstone) {
            insert(oldTable[i].key, oldTable[i].value);
        }
    }
    freeTable(oldTable, sizeof(HashEntry) * oldCapacity);
}

int HashTable::hashFunction(void* key) {
    std::uintptr_t x = reinterpret_cast<std::uintptr_t>(key);
    return (x >> 3) % capacity;
}

size_t HashTable::getSize() {
    return this->size;
}