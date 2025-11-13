package assignment04;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;

import static org.junit.jupiter.api.Assertions.*;

class SortUtilTest {

/*
 //   ArrayList<Integer> arrInterwoven6, arr6varied;
    @BeforeEach
    void setUp() {
       // arr1to6 = new ArrayList<>(Arrays.asList(1,3,5,2,4,7));
    //    arr6varied = new ArrayList<>(Arrays.asList(7,10,25,1,2,3));
    }
    */

    @org.junit.jupiter.api.Test
    void mergesort() {
        ArrayList worstCaseList = SortUtil.generateWorstCase(10000);
        SortUtil.mergesort(worstCaseList, Comparator.naturalOrder());
        for(int i = 0; i < worstCaseList.size(); i++) {
            assertEquals(worstCaseList.get(i), i + 1);
        }
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
    void mergeSmall(){
        ArrayList<Integer> listTiny =  new ArrayList<>(Arrays.asList(2,1));
        ArrayList dummy = new ArrayList();
        for(int i = 0; i < listTiny.size(); i++)
            dummy.add(0);

        SortUtil.merge(listTiny, dummy, 0, 0, 1, Comparator.naturalOrder());
        for(int i = 0; i < 2; i++)
            assertEquals(dummy.get(i), i + 1);

        ArrayList listTinyAndLate = new ArrayList(Arrays.asList(0,0,0,2,1));
        dummy = new ArrayList();
        for(int i = 0; i < listTinyAndLate.size(); i++)
            dummy.add(0);

        SortUtil.merge(listTinyAndLate, dummy, 3, 3, 4, Comparator.naturalOrder());
        assertEquals(dummy.get(3), 1);
        assertEquals(dummy.get(4), 2);
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
        ArrayList worstCaseList = SortUtil.generateWorstCase(100000);
        SortUtil.quicksort(worstCaseList, Comparator.naturalOrder());
        for(int i = 0; i < worstCaseList.size(); i++) {
            assertEquals(worstCaseList.get(i), i + 1);
        }
    }

    @org.junit.jupiter.api.Test
    void partition() {
        ArrayList<Integer> listSeparate = new ArrayList<>(Arrays.asList(7, 10, 25, 1, 2, 3));
        assertEquals(SortUtil.partition(listSeparate, 4, 0, listSeparate.size() - 1, Comparator.naturalOrder()), 1);
        assertEquals(listSeparate.get(0), 1);

        ArrayList<Integer> listSeparate2 = new ArrayList<>(Arrays.asList(7, 10, 25, 1, 2, 3));
        assertEquals(SortUtil.partition(listSeparate2, 1, 0, listSeparate2.size() - 1, Comparator.naturalOrder()), 4);
        assertEquals(listSeparate2.get(5), 25);

        ArrayList<Integer> listSeparate2WithPadding = new ArrayList<>(Arrays.asList(99, 0, 0, 7, 10, 25, 1, 2, 3));
        int part = SortUtil.partition(listSeparate2WithPadding, 4, 3, listSeparate2WithPadding.size() - 1, Comparator.naturalOrder());
        assertEquals(part, 7);
        assertEquals(listSeparate2WithPadding.get(8), 25);
        assertEquals(listSeparate2WithPadding.get(0), 99);
    }

    @org.junit.jupiter.api.Test
    void medianOf3() {
        assertEquals(1, SortUtil.medianOf3(new ArrayList<Integer>(Arrays.asList(1, 2, 3)), Comparator.naturalOrder()));
        assertEquals(0, SortUtil.medianOf3(new ArrayList<Integer>(Arrays.asList(2, 1, 3)), Comparator.naturalOrder()));
        assertEquals(2, SortUtil.medianOf3(new ArrayList<Integer>(Arrays.asList(1, 3, 2)), Comparator.naturalOrder()));
    }

    @org.junit.jupiter.api.Test
    void medianOf9() {
    }
}