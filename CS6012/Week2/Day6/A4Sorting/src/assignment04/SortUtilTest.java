package assignment04;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;

import static org.junit.jupiter.api.Assertions.*;

class SortUtilTest {


 //   ArrayList<Integer> arrInterwoven6, arr6varied;
    @BeforeEach
    void setUp() {
       // arr1to6 = new ArrayList<>(Arrays.asList(1,3,5,2,4,7));
    //    arr6varied = new ArrayList<>(Arrays.asList(7,10,25,1,2,3));
    }

    @org.junit.jupiter.api.Test
    void mergesort() {
    }

    @org.junit.jupiter.api.Test
    void mergeInterWoven() {
        ArrayList<Integer> listInterwoven = new ArrayList<>(Arrays.asList(1, 3, 5, 2, 4, 6));
        ArrayList dummy = new ArrayList();
        for(int i = 0; i < 6; i++)
            dummy.add(0);
        SortUtil.merge(listInterwoven, dummy, 0, 2, 5, Comparator.naturalOrder());
        for(int i = 0; i < 6; i++)
            assertEquals(dummy.get(i), i + 1);
    }
    @org.junit.jupiter.api.Test
    void mergeSeparate() {
        ArrayList<Integer> listSeparate = new ArrayList<>(Arrays.asList(7, 10, 25, 1, 2, 3));
        ArrayList dummy = new ArrayList();
        for(int i = 0; i < 6; i++)
            dummy.add(0);
        SortUtil.merge(listSeparate, dummy, 0, 2, 5, Comparator.naturalOrder());

        assertEquals(1, dummy.get(0));
        assertEquals(2, dummy.get(1));
        assertEquals(3, dummy.get(2));
        assertEquals(7, dummy.get(3));
        assertEquals(10, dummy.get(4));
        assertEquals(25, dummy.get(5));
    }

    @org.junit.jupiter.api.Test
    void insertionSort() {
        ArrayList<Integer> shortTest = new ArrayList<>(Arrays.asList(1, 3, 5, 2, 4, 6));
        SortUtil.insertionSort(shortTest, 0, shortTest.size() - 1, Comparator.naturalOrder());
        for(int i = 0; i < 6; i++)
            assertEquals(shortTest.get(i), i + 1);
    }

    @org.junit.jupiter.api.Test
    void quicksort() {
    }

    @org.junit.jupiter.api.Test
    void partition() {
    }
}