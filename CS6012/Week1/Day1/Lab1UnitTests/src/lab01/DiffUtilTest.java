package lab01;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class DiffUtilTest {

    private int[] arr1, arr2, arr3, arrBigNegative, arrStart, arrMiddle, arrEnd, arrBigNegativeReversed;

    @org.junit.jupiter.api.BeforeEach
    void setUp() {
        arr1 = new int[0];
        arr2 = new int[] { 3, 3, 3 };
        arr3 = new int[] { 52, 4, -8, 0, -17 };
        arrBigNegative = new int[] {-999, 1, 2};
        arrStart = new int[] {0, 1, 3, 5};
        arrMiddle = new int[] {0, 2, 3, 5, 7};
        arrEnd = new int[] {0, 2, 5, 6};
        arrBigNegativeReversed = new int[] {1, 2, -999};
    }

    @org.junit.jupiter.api.AfterEach
    void tearDown() {
        arr1 = null;
        arr2 = null;
        arr3 = null;
        arrBigNegative = null;
        arrStart = null;
        arrMiddle = null;
        arrEnd = null;
    }

    @Test
    public void emptyArray() {
        assertEquals(-1, DiffUtil.findSmallestDiff(arr1));
    }

    @Test
    public void allArrayElementsEqual() {
        assertEquals(0, DiffUtil.findSmallestDiff(arr2));
    }

    @Test
    public void smallRandomArrayElements() {
        assertEquals(4, DiffUtil.findSmallestDiff(arr3));
    }

    @Test
    public void smallestDiffBigNegative() {
        //Checking if large negative number may overwhelm what should be an absolute value diff
        assertEquals(1, DiffUtil.findSmallestDiff(arrBigNegative));
    }

    @Test
    public void smallestDiffBigNegativeReversed() {
        assertEquals(1, DiffUtil.findSmallestDiff(arrBigNegative));
    }

    @Test
    public void smallestDiffStartPair() {
        assertEquals(1, DiffUtil.findSmallestDiff(arrStart));
    }

    @Test
    public void smallestDiffEndPair() {
        assertEquals(1, DiffUtil.findSmallestDiff(arrEnd));
    }

    @Test
    public void smallestDiffStartEndControl() {
        assertEquals(1, DiffUtil.findSmallestDiff(arrMiddle));
    }




}