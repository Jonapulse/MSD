//////////////////////////////////////////////
// Created by Jonathan Pulsipher on 3/21/2026.
// Generated unit tests expected and fixed 3/22/26
/////////////////////////////////////////////

#include <gtest/gtest.h>
#include "../src/HashTable.h"

// ─── Basic Operations ────────────────────────────────────────────────────────

TEST(HashTableTest, StartsEmpty) {
    HashTable ht;
    EXPECT_EQ(ht.getSize(), 0);
}

TEST(HashTableTest, InsertIncrementsSize) {
    HashTable ht;
    ht.insert((void*)42, 21);
    EXPECT_EQ(ht.getSize(), 1);
}

TEST(HashTableTest, InsertAndGet) {
    HashTable ht;
    ht.insert((void*)42, 99);
    int size = ht.get((void*)42);
    EXPECT_EQ(size, 99);
}

TEST(HashTableTest, ContainsTrueAfterInsert) {
    HashTable ht;
    ht.insert((void*)42, 1);
    EXPECT_TRUE(ht.contains((void*)42));
}

TEST(HashTableTest, ContainsFalseForMissingKey) {
    HashTable ht;
    EXPECT_FALSE(ht.contains((void*)42));
}

TEST(HashTableTest, UpdateExistingKey) {
    HashTable ht;
    ht.insert((void*)42, 1);
    ht.insert((void*)42, 2);
    EXPECT_EQ(ht.get((void*)42), 2);
    EXPECT_EQ(ht.getSize(), 1);
}

// ─── Remove ──────────────────────────────────────────────────────────────────

TEST(HashTableTest, RemoveDecrementsSize) {
    HashTable ht;
    ht.insert((void*)42, 1);
    ht.remove((void*)42);
    EXPECT_EQ(ht.getSize(), 0);
}

TEST(HashTableTest, ContainsFalseAfterRemove) {
    HashTable ht;
    ht.insert((void*)42, 1);
    ht.remove((void*)42);
    EXPECT_FALSE(ht.contains((void*)42));
}

TEST(HashTableTest, RemoveMissingKeyNoThrow) {
    HashTable ht;
    EXPECT_NO_THROW(ht.remove((void*)42));
}

// ─── Linear Probing ──────────────────────────────────────────────────────────
// hashFunction is (address >> 3) % 16, so keys 0,8,16 all map to slot 0,
// giving us deterministic collisions to probe against.

TEST(HashTableTest, CollidingKeysAllInserted) {
    HashTable ht;
    ht.insert((void*)0,  1);
    ht.insert((void*)128, 2);
    ht.insert((void*)256, 3);
    EXPECT_EQ(ht.getSize(), 3);
}

TEST(HashTableTest, CollidingKeysAllRetrievable) {
    HashTable ht;
    ht.insert((void*)0,   1);
    ht.insert((void*)128, 2);
    ht.insert((void*)256, 3);
    EXPECT_EQ(ht.get((void*)0),   1);
    EXPECT_EQ(ht.get((void*)128), 2);
    EXPECT_EQ(ht.get((void*)256), 3);
}

TEST(HashTableTest, ProbingNotBrokenByTombstone) {
    HashTable ht;
    // Insert two colliding keys, remove the first, then find the second.
    // If tombstones stop probing instead of continuing it, get() would fail.
    ht.insert((void*)0,   1);
    ht.insert((void*)128, 2);
    ht.remove((void*)0);
    EXPECT_EQ(ht.get((void*)128), 2);
}

TEST(HashTableTest, CanReuseSlotAfterTombstone) {
    HashTable ht;
    ht.insert((void*)0, 1);
    ht.remove((void*)0);
    ht.insert((void*)0, 2);
    EXPECT_EQ(ht.get((void*)0), 2);
    EXPECT_EQ(ht.getSize(), 1);
}

// ─── Grow / Rehash ───────────────────────────────────────────────────────────

TEST(HashTableTest, GrowPreservesAllEntries) {
    HashTable ht;
    // Insert 13 items to exceed the 0.75 load factor on capacity 16
    for (int i = 1; i <= 13; i++)
        ht.insert((void*)(uintptr_t)i, i * 10);
    for (int i = 1; i <= 13; i++)
        EXPECT_EQ(ht.get((void*)(uintptr_t)i), i * 10);
}

TEST(HashTableTest, GrowPreservesSize) {
    HashTable ht;
    for (int i = 1; i <= 13; i++)
        ht.insert((void*)(uintptr_t)i, i * 10);
    EXPECT_EQ(ht.getSize(), 13);
}

// ─── Get Error Handling ──────────────────────────────────────────────────────

TEST(HashTableTest, GetMissingKeyThrows) {
    HashTable ht;
    EXPECT_THROW(ht.get((void*)42), std::runtime_error);
}