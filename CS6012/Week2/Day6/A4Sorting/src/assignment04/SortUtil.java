package assignment04;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Random;

public class SortUtil {

    final int SMALL_SORT_THRESHOLD = 100;

    ///////////////////////
    /// MergeSort & Helpers
    /**
     * Sorts list with mergeSort method, using provided comprator
     * Driver method
     *
     * @param list
     * @param comparator
     * @param <T>
     */
    public static <T> void mergesort(ArrayList<T> list, Comparator<? super T> comparator)
    {
        if(comparator == null)
            comparator = (Comparator<? super T>) Comparator.naturalOrder();

        //TODO: pre-allocate the temp array to use for this
        //mergeSortRecurse
    }


    static <T> void mergeSortRecurse(ArrayList<T> list, ArrayList<T> out, int b, int e, Comparator<? super T> comparator)
    {
        //if arr.length < 2
            // return;

        //if left > threshold
        // mergeSort(left)
        //else
        //insertion sort
        //if right > threshold
       // mergeSort(right)
        //else
        //insertion sort

       // merge(arr, left, right)
        //? Is this where we copy back from scratch? Think through it functionally. Yeah.
    }

    /**
     *
     * @param out
     * @param beg  - begin
     * @param endL - final index of L. 'beginR' == endL + 1;
     * @param endR - final index of R.
     */
    static <T> void merge(ArrayList<T> in, ArrayList<T> out, int beg, int endL, int endR, Comparator<? super T> comparator){
       int i = 0;
       int l = beg;
       int r = endL + 1;

       //Loop until l or r runs out
         //
       while(l <= endL - beg && r <= endR){
           if(comparator.compare(in.get(l), in.get(r)) <= 0){
               out.set(i, in.get(l));
               i++; l++;
           }
           else
           {
               out.set(i, in.get(r));
               i++; r++;
           }
       }

       //fill remaining ls or rs
         //
        for( ; l <= endL - beg; l++, i++)
            out.set(i, in.get(l));
        for( ; r <= endR; r++, i++)
            out.set(i, in.get(r));
    }

    /**
     *
     * @param list
     * @param b - begin index
     * @param e - end index
     * @return
     */
    public static <T> ArrayList<T> insertionSort(ArrayList<T> list, int b, int e)
    {
        return null;
    }

    ///////////////////////
    /// QuickSort & Helpers
    /**
     *
     * @param list
     * @param comparator
     */
    public static <T> void quicksort(ArrayList<T> list, Comparator<? super T> comparator){
        //
    }

    /**
     *
     * @param list
     * @param b
     * @param e
     * @param comparator
     */
    static <T> void quicksortRecurse(ArrayList<T> list, int b, int e, Comparator<? super T> comparator){
        //partition the list
        //quicksort left
        //quicksort right
    }

    /**
     *
     * @param list
     * @param pivot
     * @return index of pivot, an index all values earlier in the array are smaller, and all later are larger
     */
    static <T> int partition(ArrayList<T> list, int pivot, Comparator<? super T> comparator)
    {
        //swap pivot to end
        //left = 0;
        //right = end - 1//to not point at pivot
        //while(left < right)
            //while(arr[left < pivot)
                //left++
            //while(arr[right > pivot)
                //right--;
            //swap left/right
            //left++ right--
        //swap left and pivot
        return -1;
    }

    /**
     * Approximates the median of a list by taking the median of values at start, middle, and end
     *
     * @param list
     * @return index of the median
     */
    private <T> int medianOf3(ArrayList<T> list){
        //TODO: Figure out how to do this without sort, and with using those funky Ts
        return -1;
    }

    /**
     * Approximates the median of a list by taking the median of the "medianOf3" from each third of the list
     *
     * @param list
     * @return index of the median
     */
    private <T> int medianOf9(ArrayList<T> list)
    {
        if(list.size() < 9)
            return medianOf3(list);


        //get 9 random samples.
        //Try to minimize the median for 3 lists of 3 and do that on the forth
        return -1;
    }

    /////////////////////
    /// Case Generation
    public static ArrayList<Integer> generateBestCase(int size)
    {
        ArrayList<Integer> list = new ArrayList<>();
        for(int i = 0; i < size; i++)
        {
            list.add(i);
        }
        return list;
    }

    public static ArrayList<Integer> generateAverageCase(int size)
    {
        ArrayList<Integer> list = new ArrayList<>();
        for(int i = 0; i < size; i++)
        {
            list.add(i);
        }

        //Fisher-Yates shuffle
        Random rand = new Random();
        for(int i = list.size() - 1; i > 0; i--)
        {
            int j = rand.nextInt(i + 1);
            Collections.swap(list, i, j);
        }
        return list;
    }

    public static ArrayList<Integer> generateWorstCase(int size)
    {
        ArrayList<Integer> list = new ArrayList<>();
        for(int i = 0; i < size; i++)
        {
            list.add(size - i);
        }
        return list;
    }
}
