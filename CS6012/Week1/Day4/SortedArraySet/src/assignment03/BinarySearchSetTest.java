package assignment03;

import org.junit.jupiter.api.Assertions;

import java.util.Random;

import static org.junit.jupiter.api.Assertions.*;

class BinarySearchSetTest {

    @org.junit.jupiter.api.Test
    void comparator() {
    }

    @org.junit.jupiter.api.Test
    void first() {
        //TODO: Test NoSuchElement Exception
    }

    @org.junit.jupiter.api.Test
    void last() {
        //TODO: Test NoSuchElement Exception
    }

    @org.junit.jupiter.api.Test
    void addInOrderStandard() {
        BinarySearchSet<Integer> set = new BinarySearchSet<>();
        for(int i = 0; i < 10; i++)
        {
            set.add(i);
        }

        Assertions.assertEquals(set.first(), 0);
        Assertions.assertEquals(set.last(), 9);
        Assertions.assertEquals(set.size(), 10);
    }

    @org.junit.jupiter.api.Test
    void addOutOfOrderStandard() {
        BinarySearchSet<Integer> set = new BinarySearchSet<>();
        int[] testData = {1,9,4,3,100,-30,25};
        for(int i = 0; i < testData.length; i++) {
            set.add(Integer.valueOf(testData[i]));
        }
        Assertions.assertEquals(set.first(), -30);
        Assertions.assertEquals(set.last(), 100);
    }

    @org.junit.jupiter.api.Test
    void addOutOfOrderStandardReverseComparator() {
        //TODO: test this out
    }

    @org.junit.jupiter.api.Test
    void addRejectDuplicates(){
        BinarySearchSet<Integer> set = new BinarySearchSet<>();
        for(int i = 0; i < 10; i++)
        {
            set.add(i);
        }
        set.add(3); //Any
        set.add(0); //First
        set.add(9); //Last
        Assertions.assertEquals(set.size(), 10);
    }

    @org.junit.jupiter.api.Test
    void addGrow10000()
    {
        BinarySearchSet<Integer> set = new BinarySearchSet<>();
        for(int i = 0; i < 10000; i++)
        {
            set.add(i);
        }
        Assertions.assertEquals(set.size(), 10000);
    }

    @org.junit.jupiter.api.Test
    void addAll() {
    }

    @org.junit.jupiter.api.Test
    void removeStandard(){
        BinarySearchSet<Integer> set = new BinarySearchSet<>();
        for(int i = 0; i < 10; i++)
        {
            set.add(i);
        }
        set.remove(5); //removes 3 instead of 5, shift starts 1 down from where it should
        set.remove(0);
        set.remove(9);
        Assertions.assertFalse(set.contains(5));
        Assertions.assertFalse(set.contains(0));
        Assertions.assertFalse(set.contains(10));
        Assertions.assertFalse(set.first() == 0);
        Assertions.assertTrue(set.first() == 1);
        Assertions.assertFalse(set.last() == 9);
        Assertions.assertTrue(set.last() == 8);
        Assertions.assertTrue(set.size() == 7);
    }

    @org.junit.jupiter.api.Test
    void remove10000()
    {
        BinarySearchSet<Integer> set = new BinarySearchSet<>();
        for(int i = 0; i < 10000; i++)
        {
            set.add(i);
        }
        int laggingCheck = 1234;
        for(int i = 0; i < 10000; i++){
            if(i != laggingCheck)
                set.remove(i);
        }
        Assertions.assertEquals(set.size(), 1);
        Assertions.assertTrue(set.contains(laggingCheck));
        set.remove(laggingCheck);
        Assertions.assertTrue(set.size() == 0);
    }

    @org.junit.jupiter.api.Test
    void containsStandard() {
        BinarySearchSet<Integer> set = new BinarySearchSet<>();
        int[] testData = {1,9,4,3,100,-30,25};
        for(int i = 0; i < testData.length; i++) {
            set.add(Integer.valueOf(testData[i]));
        }
        Assertions.assertTrue(set.contains(9)); //any
        Assertions.assertTrue(set.contains(-30)); //start
        Assertions.assertTrue(set.contains(100)); //end
        Assertions.assertTrue(!set.contains(999)); //not

    }

    @org.junit.jupiter.api.Test
    void containsHuge() {
        BinarySearchSet<Integer> set = new BinarySearchSet<>();
        Random rand = new Random();
        int insertions = 10000;
        int range = 10000000;
        for(int i = 0; i < insertions; i++){
            set.add(Integer.valueOf(rand.nextInt(range)));
        }
        set.add(123456); //Test target
        Assertions.assertTrue(set.contains(123456));
    }

    @org.junit.jupiter.api.Test
    void containsAll() {
    }

    @org.junit.jupiter.api.Test
    void clear() {
    }


    @org.junit.jupiter.api.Test
    void isEmpty() {
    }

    @org.junit.jupiter.api.Test
    void iterator() {
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

    @org.junit.jupiter.api.Test
    void toArray() {
    }

    @org.junit.jupiter.api.Test
    void forEach() {
    }
}