package assignment06;

import java.util.ArrayList;
import java.util.Collection;
import java.util.NoSuchElementException;

public class BinarySearchTree<T> implements SortedSet<T>{
    @Override
    public boolean add(T item) {
        return false;
    }

    @Override
    public boolean addAll(Collection<? extends T> items) {
        return false;
    }

    @Override
    public void clear() {

    }

    @Override
    public boolean contains(T item) {
        return false;
    }

    @Override
    public boolean containsAll(Collection<? extends T> items) {
        return false;
    }

    @Override
    public T first() throws NoSuchElementException {
        return null;
    }

    @Override
    public boolean isEmpty() {
        return false;
    }

    @Override
    public T last() throws NoSuchElementException {
        return null;
    }

    @Override
    public boolean remove(T item) {
        return false;
    }

    @Override
    public boolean removeAll(Collection<? extends T> items) {
        return false;
    }

    @Override
    public int size() {
        return 0;
    }

    @Override
    public ArrayList<T> toArrayList() {
        return null;
    }
}
