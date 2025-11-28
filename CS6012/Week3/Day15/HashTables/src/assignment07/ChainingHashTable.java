package assignment07;

import java.util.Collection;
import java.util.LinkedList;

public class ChainingHashTable implements Set<String> {

    private LinkedList<String>[] storage;
    private int capacity;
    private int size;
    private final float RESIZE_FRACTION = 0.5f;
    private HashFunctor hashFunctor;

    @SuppressWarnings("unchecked")
    public ChainingHashTable(int capacity, HashFunctor functor){
        storage = (LinkedList<String>[])new LinkedList[capacity];
        this.capacity = capacity;
        this.size = 0;
        this.hashFunctor = functor;
    }

    /**
     * Adds item to Set if not duplicate
     *
     * @param item
     * @return true if item added to set, else false
     */
    @Override
    public boolean add(String item) {
        if(size / capacity >= RESIZE_FRACTION)
            expandAndRehash();

        int originalSize = size;
        int hashedIndex = compress(hashFunctor.hash(item));
        if(storage[hashedIndex] == null){
            storage[hashedIndex] = new LinkedList<>();
            storage[hashedIndex].add(item);
            size++;
        } else {
            if(!storage[hashedIndex].contains(item)) {
                storage[hashedIndex].add(item);
                size++;
            }
        }
        return size != originalSize;
    }

    /**
     * Returns an index within storage using hashCode
     *
     * @param hashCode
     * @return remainder of hashCode that indexes to storage
     */
    private int compress(int hashCode){
        //More complicated expression to handle negative modulus results in java
        return (hashCode % capacity + capacity) % capacity;
    }

    /**
     * Double capacity and re-insert each element in old storage into
     * new storage.
     */
    private void expandAndRehash(){
        capacity *= 2;
        LinkedList<String>[] oldStorage = storage;
        storage = (LinkedList<String>[])new LinkedList[capacity];
        for(int i = 0; i < oldStorage.length; i++){
            if(oldStorage[i] != null){
                for(int j = 0; j < oldStorage[i].size(); j++){
                    add(oldStorage[i].get(j));
                }
            }
        }
    }

    /**
     * Add items to set if not duplicate
     *
     * @param items
     * @return true if any items were added to Set
     */
    @Override
    public boolean addAll(Collection<? extends String> items) {
        int originalSize = size;
        for(Object item: items){
            add((String) item);
        }
        return size != originalSize;
    }

    /**
     * Resets storage, keeping capacity
     */
    @Override
    public void clear() {
        storage = (LinkedList<String>[])new LinkedList[capacity];
        this.capacity = capacity;
        this.size = 0;
    }


    /**
     * Returns true if matching String contained in Set
     *
     * @param item
     * @return true if matching item contained in Set
     */
    @Override
    public boolean contains(String item) {
        int hashedIndex = compress(hashFunctor.hash(item));
        if(storage[hashedIndex] == null){
            return false;
        } else
            return storage[hashedIndex].contains(item);
    }

    /**
     * Returns true if all Strings contained in set
     *
     * @param items
     * @return true if items contained in set
     */
    @Override
    public boolean containsAll(Collection<? extends String> items) {
        for(String item: items){
            if(!contains(item))
                return false;
        }
        return true;
    }

    /**
     * @return true if size == 0
     */
    @Override
    public boolean isEmpty() {
        return size == 0;
    }

    /**
     * Removes String from storage if present
     *
     * @param item
     * @return true if set changes as a result of this
     */
    @Override
    public boolean remove(String item) {
        int hashedIndex = compress(hashFunctor.hash(item));
        int originalSize = size;
        if(storage[hashedIndex] != null){
            if(storage[hashedIndex].remove(item))
                size--;
        }
        return originalSize != size;
    }

    /**
     * Removes all Strings from storage if present
     *
     * @param items
     * @return true if set changes as a result of this
     */
    @Override
    public boolean removeAll(Collection<? extends String> items) {
        int originalSize = size;
        for(String item: items){
            remove(item);
        }
        return originalSize != size;
    }

    /**
     * @return # of elements in storage
     */
    @Override
    public int size() {
        return size;
    }
}
