package assignment05;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.NoSuchElementException;

import static org.junit.jupiter.api.Assertions.*;

class LinkedListStackTest {

    LinkedListStack<Integer> stackEmpty;
    LinkedListStack<Integer> stackSimple;
    @BeforeEach
    void setUp() {
        stackEmpty = new LinkedListStack<>();
        stackSimple = new LinkedListStack<>();
        stackSimple.push(3);
        stackSimple.push(2);
        stackSimple.push(1);
    }

    @Test
    void clear() {
        stackSimple.clear();
        assertTrue(stackSimple.isEmpty());
    }

    @Test
    void isEmpty() {
        assertTrue(stackEmpty.isEmpty());
    }

    @Test
    void peek() {
        boolean exceptionCaught = false;
        try{
            assertEquals("", stackEmpty.peek());
        } catch(NoSuchElementException e){
            exceptionCaught = true;
        }
        assertTrue(exceptionCaught);

        assertEquals(1, stackSimple.peek());
    }

    @Test
    void pop() {
        boolean exceptionCaught = false;
        assertEquals(1, stackSimple.pop());
        assertEquals(2, stackSimple.pop());
        assertEquals(3, stackSimple.pop());
        try{
            assertEquals(4, stackSimple.pop());
        } catch(NoSuchElementException e){
            exceptionCaught = true;
        }
        assertTrue(exceptionCaught);
    }

    @Test
    void push() {
        stackEmpty.push(2);
        stackEmpty.push(1);
        assertEquals(stackEmpty.pop(), 1);
        assertEquals(stackEmpty.pop(), 2);
    }

    @Test
    void size() {
        assertEquals(stackEmpty.size(), 0);
        assertEquals(stackSimple.size(), 3);
    }
}