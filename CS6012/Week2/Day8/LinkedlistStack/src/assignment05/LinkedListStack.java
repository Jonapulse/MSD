package assignment05;

import java.util.ArrayList;
import java.util.NoSuchElementException;

public class LinkedListStack<E> implements Stack<E>{

    SinglyLinkedList<E> linkList;

    public LinkedListStack() {
        linkList = new SinglyLinkedList<>();
    }

    @Override
    public void clear() {
        linkList =  new SinglyLinkedList<>();
    }

    @Override
    public boolean isEmpty() {
        return linkList.size() == 0;
    }

    @Override
    public E peek() throws NoSuchElementException {
        if(isEmpty())
            throw new NoSuchElementException();
        return linkList.getFirst();
    }

    @Override
    public E pop() throws NoSuchElementException {
        if(isEmpty())
            throw new NoSuchElementException();
        return linkList.deleteFirst();
    }

    @Override
    public void push(E element) {
        linkList.insertFirst(element);
    }

    @Override
    public int size() {
        return linkList.size();
    }
}
