package assignment03;

import java.util.Collection;
import java.util.Comparator;
import java.util.Iterator;
import java.util.NoSuchElementException;

public class BinarySearchSet<E> implements SortedSet<E>{

    private final int DEFAULT_CAPACITY = 10;

    private E[] data_ = (E[]) new Object[DEFAULT_CAPACITY];
    private int size_ = 0;
    private int capacity_ = DEFAULT_CAPACITY; //
    private Comparator<? super E> comparator_ = null;


    public BinarySearchSet() {}

    public BinarySearchSet(Comparator<? super E> comparator) {
        comparator_ = comparator;
    }

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

    /**
     * Adds element to ordered data if not duplicate
     *
     * @param element
     * @return true if set is modified, false if not
     */
    @Override
    public boolean add(E element) {
        int insertPoint = locateInsertIndex(element);

        //Insert if start/end of data or within data and no duplicate exists.
        //
        if(insertPoint >= size_ || compare(data_[insertPoint], element) != 0) {
            if(size_ + 1 == capacity_)
                growCapacity();
            if(size_ > 0 && insertPoint < size_)
                shiftData(insertPoint, 1);
            data_[insertPoint] = element;
            size_++;
            return true;
        }
        else
            return false;
        // TODO: Test shiftData.
        // TODO: Test grow (and check that implementation)
        // TODO: than... that enough?
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

        return false;
    }

    //Code Review: "compareBranching"? Or just call it "compare"? I switched to compare because of a primal feeling in my stomach.
    /**
     * Branches between comparing with provided comparator or, if null, element Comparables.
     * @param e1, elements to compare
     * @param e2, ...
     * @return -1 if e1 < e2, 0 if e1 == e2, 1 if e1 > e2
     */
    int compare(E e1, E e2) {
        if(comparator_ != null) {
            return comparator_.compare(e1, e2);
        }
        else{
            return ((Comparable<E>)e1).compareTo(e2);
        }
    }


    //Code Review: Best way to do this? I also considered returning a 2-variable storage class, but yuck.
    //also made an attempt to test this independently as a static function. Horror!
    /**
     * Binary search returns index of element OR where it SHOULD be inserted.
     * Assumes sorted set, which BinarySearchSet requires
     *
     * @param element - search target
     * @return object - {boolean elemFound, int index}
     */
    int locateInsertIndex(E element){
        int start = 0;
        int end = size_ - 1;
        int mid = 0;
        int compare = 0;
        while(start <= end){
            mid = start + (end - start)/2;
            compare = compare(element, data_[mid]);
            if(compare == 0)
                return mid;
            else if(compare < 0)
                end = mid - 1;
            else
                start = mid + 1;
        }
        //Return last index searched if element goes before there,
        // or + 1 if element should be after
        return mid + (compare > 0 ? 1 : 0);
    }

    /**
     * Moves data_ from "start" index to end of set "shift" spaces
     * @param start
     * @param shift
     */
    void shiftData(int start, int shift){
        int loopStart = shift > 0 ? size_ - 1: start - 1;
        int loopEnd = shift > 0 ? start - 1: size_ - 1;
        int increment = shift > 0 ? -1 : 1;
        for(int i = loopStart; i != loopEnd; i += increment ){
            data_[i + shift] = data_[i];
        }
    }

    /**
     * double data capacity and copies data over
     */
    void growCapacity() {
        capacity_ = capacity_ * 2;
        E[] new_data = (E[]) new Object[capacity_];
        System.arraycopy(data_, 0, new_data, 0, size_);
        data_ = new_data;
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
