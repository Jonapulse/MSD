package assignment06;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.List;
import java.util.NoSuchElementException;

import static org.junit.jupiter.api.Assertions.*;

class BinarySearchTreeTest {

    BinarySearchTree<Integer> treeEmpty;
    BinarySearchTree<Integer> treeIntBasic;
    BinarySearchTree<String> treeStrBasic;

    @BeforeEach
    void setUp() {
        treeEmpty = new BinarySearchTree<>();
        treeIntBasic = new BinarySearchTree<>();
        treeIntBasic.addAll(List.of(4, 2, 6, 1, 3, 5, 7));
        treeStrBasic = new BinarySearchTree<>();
        treeStrBasic.addAll(List.of("aardvark", "Apple", "appleonia","adversary","auguste","Aster"));
    }

    @org.junit.jupiter.api.Test
    void add() {
        assertFalse(treeIntBasic.contains(11));
        treeIntBasic.add(11);
        assertTrue(treeIntBasic.contains(11));

        assertFalse(treeStrBasic.contains("anonymous"));
        treeStrBasic.add("anonymous");
        assertTrue(treeStrBasic.contains("anonymous"));
    }

    @Test
    void addDontDuplicate(){
        assertFalse(treeStrBasic.add("aardvark"));
    }


    @org.junit.jupiter.api.Test
    void addAll() {
        treeEmpty.addAll(List.of(1,2,3));
        assertEquals(treeEmpty.size(), 3);
        assertTrue(treeEmpty.contains(3));
    }

    @org.junit.jupiter.api.Test
    void clear() {
        treeIntBasic.clear();
        assertTrue(treeIntBasic.isEmpty());
    }

    @org.junit.jupiter.api.Test
    void contains() {
        assertTrue(treeIntBasic.contains(6));
        assertFalse(treeIntBasic.contains(99));
        assertTrue(treeStrBasic.contains("Apple"));
        assertFalse(treeStrBasic.contains("aardvarkZ"));
    }

    @org.junit.jupiter.api.Test
    void containsAll() {
        assertTrue(treeIntBasic.containsAll(List.of(1, 2,3)));
        assertFalse(treeIntBasic.containsAll(List.of(1, 2,3, -1)));
    }

    @org.junit.jupiter.api.Test
    void first() {
        boolean caughtException = false;
        try{
            treeEmpty.first();
        } catch(NoSuchElementException e){
            caughtException = true;
        }
        assertTrue(caughtException);
        assertEquals(treeIntBasic.first(), 1);
        assertEquals(treeStrBasic.first(), "Apple");
    }

    @org.junit.jupiter.api.Test
    void isEmpty() {
        assertTrue(treeEmpty.isEmpty());
        assertFalse(treeStrBasic.isEmpty());
    }

    @org.junit.jupiter.api.Test
    void last() {
        boolean caughtException = false;
        try{
            treeEmpty.first();
        } catch(NoSuchElementException e){
            caughtException = true;
        }
        assertTrue(caughtException);
        assertEquals(treeIntBasic.last(), 7);
        assertTrue(treeStrBasic.last().equals("auguste"));
    }

    @org.junit.jupiter.api.Test
    void remove() {
        boolean caughtException = false;
        try{
            treeStrBasic.remove(null);
        } catch(NullPointerException e){
            caughtException = true;
        }
        assertTrue(caughtException);

        //Empty out treeStrBasic checking size and element removal
        int startSize = treeStrBasic.size();
        System.out.println(treeStrBasic.inOrderToString());
        treeStrBasic.remove("aardvark");
        assertFalse(treeStrBasic.contains("aardvark"));
        assertEquals(startSize-1, treeStrBasic.size());
        System.out.println(treeStrBasic.inOrderToString());
        treeStrBasic.remove("Apple");
        assertFalse(treeStrBasic.contains("Apple"));
        assertEquals(startSize-2, treeStrBasic.size());
        System.out.println(treeStrBasic.inOrderToString());
        treeStrBasic.remove("appleonia");
        assertFalse(treeStrBasic.contains("appleonia"));
        assertEquals(startSize-3, treeStrBasic.size());
        System.out.println(treeStrBasic.inOrderToString());
        treeStrBasic.remove("Aster");
        System.out.println(treeStrBasic.inOrderToString());
        assertFalse(treeStrBasic.contains("Aster"));
        assertEquals(startSize-4, treeStrBasic.size());
        treeStrBasic.remove("adversary");
        System.out.println(treeStrBasic.inOrderToString());
        assertFalse(treeStrBasic.contains("adversary"));
        assertEquals(startSize-5, treeStrBasic.size());
        treeStrBasic.remove("auguste");
        System.out.println(treeStrBasic.inOrderToString());
        assertFalse(treeStrBasic.contains("auguste"));
        assertEquals(startSize-6, treeStrBasic.size());
    }

    @Test
    void removeIfNotThere() {
        assertFalse(treeStrBasic.remove("zoo"));
        assertFalse(treeEmpty.remove(99));
    }

    @org.junit.jupiter.api.Test
    void removeAll() {
        treeIntBasic.removeAll(List.of(1,2,3));
        assertEquals(treeIntBasic.size(), 4);
        assertFalse(treeEmpty.contains(3));
    }

    @org.junit.jupiter.api.Test
    void size() {
        assertTrue(treeIntBasic.size() == 7);
        assertTrue(treeStrBasic.size() == 6);
        assertTrue(treeEmpty.size() == 0);
    }

    @org.junit.jupiter.api.Test
    void toArrayList() {
        ArrayList<Integer> intAL = treeIntBasic.toArrayList();
        for(int i = 0 ; i < intAL.size() ; i++){
            assertTrue(intAL.get(i) == Integer.valueOf(i + 1));
        }
    }

    @Test
    void checkString(){
        System.out.println(treeStrBasic.inOrderToString());
        System.out.println(treeEmpty.inOrderToString());
    }
}