package assignment04;

import java.util.*;

public class SortUtil {

    final static int SMALL_SORT_THRESHOLD = 3;
    final static float RANDOM_PIVOT_FREQUENCY = 0.25f; //TODO: Find real value. 25% for debug so it happens enough to error.

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

        ArrayList<T> scratch = new ArrayList<T>();
        scratch.addAll(list);
        mergeSortRecurse(list, scratch, 0, list.size() - 1, comparator);
    }

    /**
     * Performs mergeSort recursively on list, using out to help write and copy in-place.
     *
     * @param list
     * @param out
     * @param b - start index, inclusive
     * @param e - end index, inclusive
     * @param comparator
     */
    static <T> void mergeSortRecurse(ArrayList<T> list, ArrayList<T> out, int b, int e, Comparator<? super T> comparator)
    {
        int length = e - b + 1;
        if(length < 2) //base case for full recursion, sorted
            return;
        if(length < SMALL_SORT_THRESHOLD) {
            insertionSort(list, b, e, comparator);
            return;
        }

        int mid = (b + e) / 2;
        mergeSortRecurse(list, out, b, mid, comparator);
        mergeSortRecurse(list, out, mid + 1, e, comparator);

        merge(list, out, b, mid, e, comparator);
        for(int i = b; i <= e; i++)
            list.set(i, out.get(i));
    }

    /**
     * March through in, writing the smallest sequential values from left (beg to mid) and right (mid + 1 to end) to out
     *
     * @param out
     * @param beg - begin index
     * @param mid - final index of L. 'beginR' == mid + 1;
     * @param end - final index of R.
     */
    static <T> void merge(ArrayList<T> in, ArrayList<T> out, int beg, int mid, int end, Comparator<? super T> comparator){
       int i = beg;
       int l = beg;
       int r = mid + 1;

       //Loop until l or r runs out
         //
       while(l <= mid && r <= end){
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
        for( ; l <= mid; l++, i++)
            out.set(i, in.get(l));
        for( ; r <= end; r++, i++)
            out.set(i, in.get(r));
    }

    /**
     * In-place Insertion sort, marching through array swapping values earlier until sorted
     *
     * @param out
     * @param b - begin index
     * @param e - end index
     * @return
     */
    public static <T> void insertionSort(ArrayList<T> out, int b, int e, Comparator<? super T> comparator)
    {
        for(int i = b ; i <= e; i++)
            for(int j = b; j > b && comparator.compare(out.get(j), out.get(j - 1)) <= 0; j--)
                Collections.swap(out, j, j - 1);
    }

    ///////////////////////
    /// QuickSort & Helpers
    /**
     *
     * @param list
     * @param comparator
     */
    public static <T> void quicksort(ArrayList<T> list, Comparator<? super T> comparator){
        quicksortRecurse(list, 0, list.size() - 1, comparator);
    }

    /**
     *
     * @param list
     * @param b
     * @param e
     * @param comparator
     */
    static <T> void quicksortRecurse(ArrayList<T> list, int b, int e, Comparator<? super T> comparator){
        //TODO: better pivot, occasional random
        int length = e - b + 1;
        if(length < 2) //base case for full recursion, sorted
            return;
        if(length < SMALL_SORT_THRESHOLD)
        {
            insertionSort(list, b, e, comparator);
            return;
        }

        int part = partition(list, getPivot(list, b, e, 0, comparator), b, e, comparator);
        quicksortRecurse(list, b, part - 1, comparator);
        quicksortRecurse(list, part + 1, e, comparator);
    }

    /**
     * re-orders list, placing pivot in order, smaller elements left, larger elements right (only pivot order guaranteed)
     *
     * @param list
     * @param pivot
     * @return index of pivot, an index all values earlier in the array are smaller, and all later are larger
     */
    static <T> int partition(ArrayList<T> list, int pivot, int b, int e, Comparator<? super T> comparator)
    {
        Collections.swap(list, pivot, e);
        int left = b;
        int right = e - 1;
        while(left < right)
        {
            while(comparator.compare(list.get(left), list.get(e)) <= 0 && left < right)
                left++;
            while(comparator.compare(list.get(right), list.get(e)) >= 0 && right > left)
                right--;
            if(left < right) {
                Collections.swap(list, left, right);
                left++; right--;
            }
        }
        //Move right back if it overshot
        if(comparator.compare(list.get(right), list.get(e)) <= 0)
            right++;

        Collections.swap(list, right, e);
        return right;
    }

    /**
     * Utility class to switch between pivot methods
     * mode 0 - middle index
     * mode 1 - random
     * mode 2 - median of 3 (if I wanna get fancy I'll implement median of 9)
     *
     * @param list
     * @param b - beg index, inclusive
     * @param e - end index, inclusive
     * @param mode - type of pivot selection
     * @return index of pivot
     */
    static <T> int getPivot (ArrayList<T> list, int b, int e, int mode, Comparator<? super T> comparator)
    {
        switch(mode){
            case 0: //middle
                return b + (e - b)/2;
            case 1: //random
                Random rand = new Random();
                return b + rand.nextInt(e - b);
            case 2: //median of sample
                //TODO: This is returning a value. Adjust it to return the index.
                ArrayList<T> sample = new ArrayList<>();
                sample.add(list.get(b));
                sample.add(list.get(b + (e - b)/2));
                sample.add(list.get(e));
                return medianOf3(sample, comparator);
            default: //start
                return b;
        }
    }

    /**
     * Approximates the median of a list by taking the median of values at start, middle, and end
     *
     * @param list
     * @return index of the median
     */
    static <T> int medianOf3(ArrayList<T> list, Comparator<? super T> comparator){
        if(comparator.compare(list.get(0),list.get(1)) >= 0){
            if(comparator.compare(list.get(0),list.get(2)) < 0)
                return 0;
            else if (comparator.compare(list.get(1),list.get(2)) >= 0)
                return 2;
            else
                return 1;
        } else if (comparator.compare(list.get(1),list.get(2)) < 0)
            return 1;
        else if (comparator.compare(list.get(0),list.get(2)) >= 0)
            return 0;
        else
            return 2;
    }

    /**
     * Approximates the median of a list by taking the median of the "medianOf3" from each third of the list
     *
     * @param list
     * @return index of the median
     */
    static <T> int medianOf9(ArrayList<T> list, Comparator<? super T> comparator)
    {
        if(list.size() < 9)
            return medianOf3(list, comparator);

        //NOTE: Note yet implemented.
  //      ArrayList<Integer> medians = new ArrayList<Integer>();
   //     medians.add(list.get(medianOf3(list.subList(0, 2), comparator)));
        return -1;
    }

    /////////////////////
    /// Case Generation
    public static ArrayList<Integer> generateBestCase(int size)
    {
        ArrayList<Integer> list = new ArrayList<>();
        for(int i = 1; i <= size; i++)
        {
            list.add(i);
        }
        return list;
    }

    public static ArrayList<Integer> generateAverageCase(int size)
    {
        ArrayList<Integer> list = new ArrayList<>();
        for(int i = 1; i <= size; i++)
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
