package assignment05;

import java.util.Iterator;
import java.util.NoSuchElementException;

public class SinglyLinkedList<E> implements List<E>{

    /**
     * Node storing E value and Node next for LinkedList
     */
    class Node<E> {
        E value = null;
        Node<E> next = null;
        public Node() {}
        public Node(E value) {
            this.value = value;
        }
        public Node(E value, Node<E> next) {
            this.value = value;
            this.next = next;
        }
        public E getValue() {
            return value;
        }
        public void setValue(E value) {
            this.value = value;
        }
        public Node<E> getNext() {
            return next;
        }
        public void setNext(Node<E> next) {
            this.next = next;
        }
    }

    /**
     * We store header, an empty Node before node index 0, for functions that use the node before
     * the target node to update the list like insert and remove
     */
    Node<E> header;
    int size_;

    public SinglyLinkedList(){
        header = new Node<E>(null, null);
        size_ = 0;
    }

    /**
     *
     * @param element
     */
    @Override
    public void insertFirst(E element) {
        Node<E> newNode = new Node<>(element, header.next);
        header.setNext(newNode);
        size_++;
    }

    /**
     *
     * @param index
     * @param element
     * @throws IndexOutOfBoundsException
     */
    @Override
    public void insert(int index, E element) throws IndexOutOfBoundsException {
        if(index < 0 || index > size_)
            throw new IndexOutOfBoundsException();
        Node previousNode = getNodeBeforeIndex(index);
        if(previousNode == header)
            System.out.println("Oh no it's header");
        Node<E> newNode = new Node<>(element, previousNode.next);
        previousNode.setNext(newNode);
        size_++;
    }

    /**
     *
     * @return
     * @throws NoSuchElementException
     */
    @Override
    public E getFirst() throws NoSuchElementException {
        if(header.getNext() == null)
            throw new NoSuchElementException();
        return header.getNext().getValue();
    }

    /**
     *
     * @param index
     * @return
     */
    private Node<E> getNodeBeforeIndex(int index) {
        Node<E> node = header;
        for(int i = -1; i < index - 1; i++)
            node = node.getNext();
        return node;
    }

    /**
     *
     * @param index - the specified position
     * @return
     * @throws IndexOutOfBoundsException
     */
    @Override
    public E get(int index) throws IndexOutOfBoundsException {
        if(index < 0 || index >= size_)
            throw new IndexOutOfBoundsException();
        Node<E> nodeBefore =  getNodeBeforeIndex(index);
        return nodeBefore.getNext().getValue();
    }

    /**
     *
     * @return
     * @throws NoSuchElementException
     */
    @Override
    public E deleteFirst() throws NoSuchElementException {
        if(size_ == 0)
            throw new NoSuchElementException();
        E deletedElement = header.next.value;
        header.next = header.next.next;
        size_--;
        return deletedElement;
    }

    /**
     *
     * @param index - the specified position
     * @return
     * @throws IndexOutOfBoundsException
     */
    @Override
    public E delete(int index) throws IndexOutOfBoundsException {
        if(index < 0 || index >= size_)
            throw new IndexOutOfBoundsException();
        Node<E> nodeBefore = getNodeBeforeIndex(index);
        E deletedElement = nodeBefore.getNext().value;
        nodeBefore.next = nodeBefore.next.next;
        size_--;
        return deletedElement;
    }

    /**
     *
     * @param element
     * @return index of E or -1 if not found
     */
    @Override
    public int indexOf(E element) {
        Node<E> searchNode = header;
        int index = 0;
        while(searchNode.getNext() != null)
        {
            if(searchNode.getNext().getValue().equals(element))
                break;
            searchNode = searchNode.getNext();
            index++;
        }
        if(searchNode.getNext() == null)
            return -1;
        else
            return index;
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
    public boolean isEmpty() {
        return size_ == 0;
    }

    /**
     *
     */
    @Override
    public void clear() {
        size_ = 0;
        header = new Node<E>(null, null);
    }

    /**
     *
     * @return
     */
    @Override
    public Object[] toArray() {
        Object[] array = new Object[size_];
        Node<E> node = header;
        int index = 0;
        while(node.getNext() != null){
            array[index++] = node.getNext().getValue();
            node = node.getNext();
        }
        return array;
    }

    /**
     *
     * @return
     */
    @Override
    public Iterator iterator() {
        return new SinglyLinkedListIterator();
    }

    public class SinglyLinkedListIterator implements Iterator<E> {
        private int nextIndex = 0;
        private Node<E> prevNode = header;
        private Node<E> currentNode = null;
        private boolean canRemove = false;

        public SinglyLinkedListIterator() {
            currentNode = header;
        }

        /**
         * @return true if nextIndex within size
         */
        @Override
        public boolean hasNext() throws NoSuchElementException {
            return currentNode.getNext() != null;
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
            prevNode = currentNode;
            currentNode = currentNode.getNext();
            return currentNode.getValue();
        }

        /**
         * Removes element at nextIndex if next has been called for that element
         * O(1) implementation
         * @throws IllegalStateException
         */
        @Override
        public void remove() {
            if(!canRemove)
                throw new IllegalStateException();
            prevNode.next = currentNode.next;
            currentNode = prevNode;
            size_--;
            canRemove = false;
        }
    }

    //Utility class for Testing
    public String toString() {
        String retStr = "";
        Node <E> node = header.getNext();
        while(node != null){
            retStr += node.getValue() + "\n";
            node = node.getNext();
        }
        return retStr;
    }

}
