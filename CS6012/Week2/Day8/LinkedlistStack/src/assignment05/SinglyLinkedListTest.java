package assignment05;

import org.junit.jupiter.api.BeforeEach;

import java.util.NoSuchElementException;

import static org.junit.jupiter.api.Assertions.*;

class SinglyLinkedListTest {

    SinglyLinkedList<Integer> listEmptyInt;
    SinglyLinkedList<String> listEmptyStr;
    SinglyLinkedList<Integer> listBasicInt;
    SinglyLinkedList<String> listBasicStr;
    @BeforeEach
    void setUp() {
        listEmptyInt = new SinglyLinkedList<Integer>();
        listEmptyStr =  new SinglyLinkedList<String>();
        listBasicInt = new SinglyLinkedList<Integer>();
        listBasicStr = new SinglyLinkedList<String>();
        for(int i = 10; i > 0; i--)
            listBasicInt.insertFirst(Integer.valueOf(i));
        listBasicStr.insertFirst("three");
        listBasicStr.insertFirst("two");
        listBasicStr.insertFirst("one");
    }

    @org.junit.jupiter.api.Test
    void insertFirst() {
        listEmptyInt.insertFirst(1);
        listEmptyStr.insertFirst("Hello");

        assertEquals(listEmptyInt.getFirst(), 1);
        assertEquals(listEmptyStr.getFirst(),"Hello");
    }


    @org.junit.jupiter.api.Test
    void insert() {
        listEmptyInt.insert(0, Integer.valueOf(12));
        assertEquals(listEmptyInt.getFirst(), Integer.valueOf(12));
        listEmptyInt.insert(1, Integer.valueOf(13));
        assertEquals(listEmptyInt.get(1), Integer.valueOf(13));
        listEmptyInt.insert(0, Integer.valueOf(11));
        assertEquals(listEmptyInt.getFirst(), Integer.valueOf(11));

        listBasicStr.insert(1, "break");
        assertEquals(listBasicStr.get(1), "break");
        assertEquals(listBasicStr.get(2), "two");
    }

    @org.junit.jupiter.api.Test
    void getFirst() {
        assertEquals(listBasicInt.getFirst(), 1);
        assertEquals(listBasicStr.getFirst(), "one");
    }

    @org.junit.jupiter.api.Test
    void get() {
        for(int i = 10; i > 0; i--)
            assertEquals(listBasicInt.get(i), Integer.valueOf(i));
    }

    @org.junit.jupiter.api.Test
    void deleteFirst() {
        assertEquals(listBasicStr.deleteFirst(), "one");
        assertEquals(listBasicStr.getFirst(), "two");
        boolean caughtException = false;
        try{
            listEmptyInt.deleteFirst();
        } catch (NoSuchElementException e){
            caughtException = true;
        }
        assertTrue(caughtException);
    }

    @org.junit.jupiter.api.Test
    void delete() {
    }

    @org.junit.jupiter.api.Test
    void indexOf() {
        for(int i = 10; i > 0; i--)
            assertEquals(listBasicInt.indexOf(i), Integer.valueOf(i - 1));
        assertEquals(listBasicStr.indexOf("two"), Integer.valueOf(1));

        assertEquals(listBasicStr.indexOf("not_in_list"), -1);
    }

    @org.junit.jupiter.api.Test
    void size() {
        assertTrue(listEmptyInt.size() == 0);
        assertTrue(listEmptyStr.size() == 0);
        assertTrue(listBasicInt.size() == 10);
        assertTrue(listBasicStr.size() == 3);
    }

    @org.junit.jupiter.api.Test
    void isEmpty() {
        assertTrue(listEmptyInt.isEmpty());
        assertTrue(listEmptyStr.isEmpty());
    }

    @org.junit.jupiter.api.Test
    void clear() {
        listBasicInt.clear();
        assertTrue(listEmptyInt.isEmpty());
    }

    @org.junit.jupiter.api.Test
    void toArray() {
    }

    @org.junit.jupiter.api.Test
    void iterator() {
    }
}