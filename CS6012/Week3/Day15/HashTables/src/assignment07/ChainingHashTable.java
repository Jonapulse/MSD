package assignment07;

import java.util.Collection;
import java.util.LinkedList;

public class ChainingHashTable implements Set<String> {

    private LinkedList<String>[] storage;

    @SuppressWarnings("unchecked")
    public ChainingHashTable(int capacity, HashFunctor functor){
        storage = (LinkedList<String>[])new LinkedList[capacity];
    }


    @Override
    public boolean add(String item) {
        return false;
    }

    @Override
    public boolean addAll(Collection<? extends String> items) {
        return false;
    }

    @Override
    public void clear() {

    }

    @Override
    public boolean contains(String item) {
        return false;
    }

    @Override
    public boolean containsAll(Collection<? extends String> items) {
        return false;
    }

    @Override
    public boolean isEmpty() {
        return false;
    }

    @Override
    public boolean remove(String item) {
        return false;
    }

    @Override
    public boolean removeAll(Collection<? extends String> items) {
        return false;
    }

    @Override
    public int size() {
        return 0;
    }
}
