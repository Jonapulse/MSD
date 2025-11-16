package assignment05;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.net.MalformedURLException;
import java.net.URL;
import java.util.NoSuchElementException;

import static org.junit.jupiter.api.Assertions.*;

class WebBrowserTest {

    WebBrowser testBrowserEmpty;
    WebBrowser testBrowserSimple;

    @BeforeEach
    void setUp() throws MalformedURLException {
        testBrowserEmpty = new WebBrowser();
        SinglyLinkedList<URL> urlList = new SinglyLinkedList<>();
        urlList.insertFirst(new URL("https://www.google.com"));
        urlList.insertFirst(new URL("https://www.dropout.tv"));
        urlList.insertFirst(new URL("https://www.youtube.com"));
        testBrowserSimple = new WebBrowser(urlList);
    }

    @Test
    void visit() throws MalformedURLException {
        testBrowserEmpty.visit(new URL("https://www.omfgdogs.com"));
        boolean caughtException = false;
        try{
            testBrowserEmpty.back();
        } catch (NoSuchElementException e){
            caughtException = true;
        }
        assertTrue(caughtException);

        assertEquals(testBrowserSimple.back().toString(), "https://www.dropout.tv");
    }

    @Test
    void back() {
        boolean caughtException = false;
        try{
            testBrowserEmpty.back();
        } catch (NoSuchElementException e){
            caughtException = true;
        }
        assertTrue(caughtException);
    }

    @Test
    void forward() {
        boolean caughtException = false;
        try{
            testBrowserEmpty.back();
        } catch (NoSuchElementException e){
            caughtException = true;
        }
        assertTrue(caughtException);

        assertEquals(testBrowserSimple.back().toString(), "https://www.dropout.tv");
        assertEquals(testBrowserSimple.forward().toString(), "https://www.youtube.com");
    }

    @Test
    void history() {
        assertTrue(testBrowserEmpty.history().isEmpty());
        SinglyLinkedList<URL> history = testBrowserSimple.history();
        assertEquals(history.get(0).toString(),  "https://www.youtube.com");
        assertEquals(history.get(1).toString(),  "https://www.dropout.tv");
        assertEquals(history.get(2).toString(),  "https://www.google.com");
    }
}