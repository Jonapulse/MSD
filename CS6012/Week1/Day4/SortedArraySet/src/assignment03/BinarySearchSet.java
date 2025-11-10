package assignment03;

import java.util.Collection;
import java.util.Comparator;
import java.util.Iterator;
import java.util.NoSuchElementException;

public class BinarySearchSet<E> implements SortedSet<E>{

    private final int DEFAULT_CAPACITY = 10;
    private final int GROW_FACTOR = 2; //NOTE: I considered a 'more sophisticated' growth factor that grew larger arrays less,
    //but optimizing without a clear target (and doing more work...) felt wrong
    private E[] data_ = (E[]) new Object[DEFAULT_CAPACITY];
    private int size_ = 0;
    private int capacity_ = DEFAULT_CAPACITY; //
    private Comparator<? super E> comparator_ = null;


    public BinarySearchSet() {}

    public BinarySearchSet(Comparator<? super E> comparator) {
        comparator_ = comparator;
    }

    //TODO: decide on helper functions
    //shared findMemberOrInsertPoint?
    //shared copyArray (for grow/shrink). Share function with addRemAll? That stuff is stretch
        //share functionality with insert's add? Or maybe it just takes new array size and a list of lists to add
        //NOTE: make sure this isn't something better accomplished with basic functions. Might not need to share.

    /**
     *
     * @return
     */
    @Override
    public Comparator<? super E> comparator() {
        return comparator_;
    }

    /**
     *
     * @return
     * @throws NoSuchElementException
     */
    @Override
    public E first() throws NoSuchElementException {
        try{
            return data_[0];
        } catch(NoSuchElementException e){
            throw e;
        }
    }

    /**
     *
     * @return
     * @throws NoSuchElementException
     */
    @Override
    public E last() throws NoSuchElementException {
        try{
            return data_[size_ - 1];
        } catch(NoSuchElementException e){
            throw e;
        }
    }

    //Code Review: Best way to do this? I also considered returning a 2-variable storage class, but yuck.
    //also made an attempt to test this independently as a static function. Horror!
    /**
     * Binary search returns index of element OR where it SHOULD be inserted.
     * Assumes sorted set, which BinarySearchSet requires
     * @param element - search target
     * @return object - {boolean elemFound, int index}
     */
    int locateWhereDataShouldBe(E element, E[] data, int size, Comparator<? super E> comparatorMe){
        int start = 0;
        int end = size - 1;
        int mid = 0;
        while(start <= end){
            mid = start + (end - start)/2;
            int compare = (comparatorMe != null) ? comparator().compare(element, data[mid]) :
                    ((Comparable<E>)element).compareTo(element);
            if(compare == 0)
                return mid;
            else if(compare < 0)
                end = mid - 1;
            else
                start = mid + 1;
        }
        return mid;
    }

    /**
     *
     * @param element
     * @return
     */
    @Override
    public boolean add(E element) {
        //TODO:
        // binary search for where to add it.
        // did you find it? Don't add.
        // otherwise, get the index of insertion where search ended (where you would otherwise return -1
        // when you add, shift every element forward
        return false;
    }

    /**
     *
     * @param elements
     * @return
     */
    @Override
    public boolean addAll(Collection<? extends E> elements) {
        //TODO:
        // think of a 'clever boy' algorithm here. Can it work? Would it be better? Would it be worth it? Can you make it play nice with add? They should share helper functions
        // Shared: find where to insert (or no insert)
        // Shared: do the insert with the moves, but in a way that could accept multiple inserts? An ordered list of index/value
        return false;
    }

    /**
     *
     */
    @Override
    public void clear() {
        capacity_ = DEFAULT_CAPACITY;
        data_ = (E[]) new Object[DEFAULT_CAPACITY];
        size_ = 0;
    }

    /**
     *
     * @param element
     * @return
     */
    @Override
    public boolean contains(E element) {
        //TODO:
        //Shared: binary search from add
        return false;
    }

    /**
     *
     * @param elements
     * @return
     */
    @Override
    public boolean containsAll(Collection<? extends E> elements) {
        //TODO: trivial. contains, return false early on any failure.
        return false;
    }

    /**
     *
     * @return
     */
    @Override
    public boolean isEmpty() {
        return size_ == 0;
    }

    /**
     *
     * @return
     */
    @Override
    public Iterator<E> iterator() {
        //Check your class notes. Should be straight-forward, but
        //I should probably hold on this until the rest of the stuff.
        return null;
    }

    /**
     *
     * @param element
     * @return
     */
    @Override
    public boolean remove(E element) {
        //TODO:
        //same path as add
        //size-- (unless not found)
        return false;
    }

    /**
     *
     * @param elements
     * @return
     */
    @Override
    public boolean removeAll(Collection<? extends E> elements) {
        //TODO:
        //same path as add
        //size-- (unless not found)
        return false;
    }

    /**
     *
     * @return
     */
    @Override
    public int size() {
        return size_;
    }

    /**
     *
     * @return
     */
    @Override
    public Object[] toArray() {
        return data_;
    }
}
