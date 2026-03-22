//////////////////////////////////////////
// Created by Jonathan Pulsipher 3/15/26
// Implementation of a Linear-probing hash table
//////////////////////////////////////////

#include "HashTable.h"
#include <cstdint>
#include <stdexcept>

HashTable::HashTable() {
    size = 0;
    capacity = INITIAL_CAPACITY;
    table.resize(capacity, {nullptr, 0, false, true});
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
    std::vector<HashEntry> forRehash;
    for (int i = 0; i < capacity; i++) {
        if (!table[i].empty)
            forRehash.push_back(table[i]);
    }
    capacity *= GROW_FACTOR;
    table.assign(capacity, {nullptr, 0, false, true});
    size = 0;
    for (HashEntry entry : forRehash) {
        insert(entry.key, entry.value);
    }
}

int HashTable::hashFunction(void* key) {
    std::uintptr_t x = reinterpret_cast<std::uintptr_t>(key);
    return (x >> 3) % capacity;
}

int HashTable::getSize() {
    return this->size;
}