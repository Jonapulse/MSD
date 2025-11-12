package assignment04;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Random;

public class SortUtil {

    final int SMALL_SORT_THRESHOLD = 100;

    public static <T> void mergesort(ArrayList<T> list, Comparator<? super T> comparator)
    {
        //MergeSort. Should switch to insertion sort when the size of the sublist to be sorted is small enough.
    }

    public static <T> void quicksort(ArrayList<T> list, Comparator<? super T> comparator){

    }

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

}
