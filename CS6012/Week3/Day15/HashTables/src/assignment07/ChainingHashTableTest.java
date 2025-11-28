package assignment07;

import org.junit.jupiter.api.BeforeEach;

import java.util.Arrays;

import static org.junit.jupiter.api.Assertions.*;

class ChainingHashTableTest {

    ChainingHashTable hashTableBasic;
    ChainingHashTable hashTableEmpty;
    ChainingHashTable hashTablePreExpand;
    ChainingHashTable hashTableMidHashFunctorTest;
    ChainingHashTable hashTableBadHashFunctorTest;

    @BeforeEach
    void setUp() {
        hashTableBasic = new ChainingHashTable(20, new GoodHashFunctor());
        hashTableBasic.addAll(Arrays.asList("apples", "bananas", "pears", "kumquats", "kiwis"));
        hashTableEmpty = new ChainingHashTable(20, new GoodHashFunctor());
        hashTablePreExpand = new ChainingHashTable(10, new GoodHashFunctor());
        hashTablePreExpand.addAll(Arrays.asList("apples", "bananas", "pears", "kumquats"));
        hashTableMidHashFunctorTest = new ChainingHashTable(20, new MediocreHashFunctor());
        hashTableMidHashFunctorTest.addAll(Arrays.asList("apples", "bananas", "pears", "kumquats", "kiwis"));
        hashTableBadHashFunctorTest = new ChainingHashTable(20, new BadHashFunctor());
        hashTableBadHashFunctorTest.addAll(Arrays.asList("apples", "bananas", "pears", "kumquats", "kiwis"));

    }

    @org.junit.jupiter.api.Test
    void add() {
    }

    @org.junit.jupiter.api.Test
    void addAll() {
    }

    @org.junit.jupiter.api.Test
    void clear() {
    }

    @org.junit.jupiter.api.Test
    void contains() {
    }

    @org.junit.jupiter.api.Test
    void containsAll() {
    }

    @org.junit.jupiter.api.Test
    void isEmpty() {
    }

    @org.junit.jupiter.api.Test
    void remove() {
    }

    @org.junit.jupiter.api.Test
    void removeAll() {
    }

    @org.junit.jupiter.api.Test
    void size() {
    }
}