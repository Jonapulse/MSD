package assignment07;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

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
        hashTablePreExpand = new ChainingHashTable(9, new GoodHashFunctor());
        hashTablePreExpand.addAll(Arrays.asList("apples", "bananas", "pears", "kumquats"));
        hashTableMidHashFunctorTest = new ChainingHashTable(20, new MediocreHashFunctor());
        hashTableMidHashFunctorTest.addAll(Arrays.asList("apples", "bananas", "pears", "kumquats", "kiwis"));
        hashTableBadHashFunctorTest = new ChainingHashTable(20, new BadHashFunctor());
        hashTableBadHashFunctorTest.addAll(Arrays.asList("apples", "bananas", "pears", "kumquats", "kiwis"));

    }

    @org.junit.jupiter.api.Test
    void add() {
        assertTrue(hashTableEmpty.add("oranges"));
        assertFalse(hashTableEmpty.add("oranges")); //no duplicate
        assertTrue(hashTableEmpty.contains("oranges"));

        assertTrue(hashTableBasic.add("oranges"));
        assertTrue(hashTableBasic.contains("oranges"));

        assertTrue(hashTablePreExpand.add("oranges"));
        assertTrue(hashTablePreExpand.contains("oranges"));
        assertTrue(hashTablePreExpand.contains("apples"));
    }

    @Test
    void stressAddAndRemove() {
        for(int i = 0; i < 1_000_000; i++) {
            hashTableEmpty.add(i + "");
        }
        assertTrue(hashTableEmpty.contains("123456"));
        for(int i = 0; i < 1_000_000; i++) {
            hashTableEmpty.remove(i + "");
        }
        assertFalse(hashTableEmpty.contains("123456"));
        assertTrue(hashTableEmpty.isEmpty());
    }

    @org.junit.jupiter.api.Test
    void clear() {
        hashTableBasic.clear();
        assertTrue(hashTableBasic.isEmpty());
        assertTrue(hashTableBasic.size() == 0);
    }

    @org.junit.jupiter.api.Test
    void contains() {
        assertTrue(hashTableBasic.contains("apples"));
        assertFalse(hashTableBasic.contains("oranges"));
        assertFalse(hashTableEmpty.contains("apples"));
    }

    @org.junit.jupiter.api.Test
    void containsAll() {
        assertTrue(hashTableBasic.containsAll(Arrays.asList("apples", "bananas")));
        assertFalse(hashTableBasic.containsAll(Arrays.asList("apples", "pears", "oranges")));
    }

    @org.junit.jupiter.api.Test
    void isEmpty() {
        assertTrue(hashTableEmpty.isEmpty());
        assertFalse(hashTableBasic.isEmpty());
    }

    @org.junit.jupiter.api.Test
    void remove() {
        assertTrue(hashTableBasic.remove("apples"));
        assertFalse(hashTableBasic.contains("apples"));
        assertFalse(hashTableBasic.remove("chocolate"));
    }

    @org.junit.jupiter.api.Test
    void size() {
        assertEquals(5, hashTableBasic.size());
        assertEquals(0, hashTableEmpty.size());
        assertTrue(hashTablePreExpand.add("filler"));
        assertEquals(5, hashTablePreExpand.size());
        assertTrue(hashTablePreExpand.remove("filler"));
        assertEquals(4, hashTablePreExpand.size());
    }
}