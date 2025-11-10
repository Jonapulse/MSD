package assignment03;

import java.util.Collection;
import java.util.Comparator;
import java.util.Iterator;
import java.util.NoSuchElementException;
import java.util.function.Consumer;

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
     * @return user-provided comparator, or null if defaulting to E.compareTo()
     */
    @Override
    public Comparator<? super E> comparator() {
        return comparator_;
    }

    /**
     * @return first element of data
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
     * @return final element of data
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
        //Insert if start/end of data or within data and no duplicate exists.
        //
        int insertIndex = locateInsertIndex(element);
        if(insertIndex >= size_ || compare(data_[insertIndex], element) != 0) {
            if(size_ + 1 == capacity_)
                growCapacity();
            if(size_ > 0 && insertIndex < size_)
                shiftData(insertIndex, 1);
            data_[insertIndex] = element;
            size_++;
            return true;
        }
        else
            return false;
    }

    //Code Review - considering optimization to look up all insertions and do one big swap
     //store all insertion points in ordered list of {insertIndex, element}
     //resize array if necessary
     //step through, copying array or filling from ordered list
     //(removeAll same deal)
    /**
     * @param elements
     * @return true if data changed, else false
     */
    @Override
    public boolean addAll(Collection<? extends E> elements) {
        boolean atLeastOneChange = false;
        for(E element : elements)
            if(add(element))
                atLeastOneChange = true;
        return atLeastOneChange;
    }

    /**
     * Removes element from data if present
     *
     * @param element
     * @return true if element removed, false if not found
     */
    @Override
    public boolean remove(E element) {
        if(size_ == 0)
            return false;

        //If the requested data is at insert index, remove it
        //
        int insertIndex = locateInsertIndex(element);
        if(compare(data_[insertIndex], element) == 0) {
            shiftData(insertIndex, -1);
            size_--;
            return true;
        }
        else
            return false;
    }

    /**
     * @param elements
     * @return true if data changed, else false
     */
    @Override
    public boolean removeAll(Collection<? extends E> elements) {
        boolean atLeastOneChange = false;
        for(E element : elements)
            if(remove(element))
                atLeastOneChange = true;
        return atLeastOneChange;
    }


    /**
     * @param element
     * @return true if element present in set
     */
    @Override
    public boolean contains(E element) {
        int insertIndex = locateInsertIndex(element);
        if(insertIndex >= size_)
            return false;
        return compare(data_[insertIndex], element) == 0;
    }

    /**
     * @param elements
     * @return true if all elements present in set
     */
    @Override
    public boolean containsAll(Collection<? extends E> elements) {
        for(E element : elements)
            if(!contains(element))
                return false;
        return true;
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
        int loopStart = shift > 0 ? size_ - 1: start + 1;
        int loopEnd = shift > 0 ? start - 1: size_;
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
     * empties set, resetting to default
     */
    @Override
    public void clear() {
        capacity_ = DEFAULT_CAPACITY;
        data_ = (E[]) new Object[DEFAULT_CAPACITY];
        size_ = 0;
    }

    /**
     * @return true if empty
     */
    @Override
    public boolean isEmpty() {
        return size_ == 0;
    }

    /**
     * @return
     */
    @Override
    public Iterator<E> iterator() {
       return new BinarySearchIterator<E>();
    }

    class BinarySearchIterator<E> implements Iterator<E> {
        private int nextIndex = 0;
        private boolean canRemove = false;

        /**
         * @return true if nextIndex within size
         */
        @Override
        public boolean hasNext() throws NoSuchElementException {
            return nextIndex < size_;
        }

        /**
         * @return next element if present
         * @throws NoSuchElementException
         */
        @Override
        public E next() {
            if(!hasNext())
                throw new NoSuchElementException();
            canRemove = true;
            return (E) data_[nextIndex++];
        }

        /**
         * Removes element at nextIndex if next has been called for that element,
         * @throws IllegalStateException
         */
        @Override
        public void remove() {
            if(!canRemove)
                throw new IllegalStateException();
            BinarySearchSet.this.remove(data_[nextIndex]);
            canRemove = false;
        }

        /**
         * not implementing
         */
        @Override
        public void forEachRemaining(Consumer<? super E> action) {
            Iterator.super.forEachRemaining(action);
        }
    }

    /**
     * @return number of elements in the array
     */
    @Override
    public int size() {
        return size_;
    }

    /**
     * Array of data containing E as objects
     * @return the data
     */
    @Override
    public Object[] toArray() {
        Object[] array = new Object[size_];
        for(int i = 0; i < size_; i++)
            array[i] = (Object)data_[i];
        return array;
    }
}
