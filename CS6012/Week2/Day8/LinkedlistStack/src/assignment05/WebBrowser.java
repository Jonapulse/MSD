package assignment05;

import java.net.URL;
import java.util.NoSuchElementException;

public class WebBrowser {

    Stack<URL> backlog = new LinkedListStack<>();
    URL currentPage = null;
    Stack<URL> frontlog = new LinkedListStack<>();;

    public WebBrowser() {}

    /**
     * Constructor - initializes WebBrowser with 1st element as current page
     * @param history - ordered list of URLs, beginning with the current, open page
     */
    public WebBrowser(SinglyLinkedList<URL> history){
        currentPage = history.deleteFirst();

        //Unload history into stack, then load back into backlog to get most recent
        //page at top of stack
         //
        Stack<URL> backLogUnloading = new LinkedListStack<>();
        while(!history.isEmpty())
            backLogUnloading.push(history.deleteFirst());
        while(!backLogUnloading.isEmpty())
            backlog.push(backLogUnloading.pop());
    }

    /**
     * Updates current page to webpage, clearing frontlog and adding the previously
     * current page to backlog
     * @param webpage
     */
    public void visit(URL webpage){
        frontlog.clear();
        if(currentPage != null)
            backlog.push(currentPage);
        currentPage = webpage;
    }

    /**
     * sets current page to the top of the backlog and adds the previously current
     * page to the frontlog
     * @return URL of the new current page
     * @throws NoSuchElementException
     */
    public URL back() throws NoSuchElementException {
        if(backlog.isEmpty())
            throw new NoSuchElementException();

        frontlog.push(currentPage);
        currentPage = backlog.pop();
        return currentPage;
    }

    /**
     * sets current page to the top of the frontlog and adds the previously current
     * page to the backlog
     * @return URL of the new current page
     * @throws NoSuchElementException
     */
    public URL forward() throws NoSuchElementException {
        if(frontlog.isEmpty())
            throw new NoSuchElementException();
        backlog.push(currentPage);
        currentPage = frontlog.pop();
        return currentPage;
    }

    /**
     * @return a singly-linked list starting with the current page and continuing
     * "backwards in time", ending with the first page visited
     */
    public SinglyLinkedList<URL> history() {
        SinglyLinkedList<URL> history = new SinglyLinkedList<>();

        if(currentPage == null) //No pages visited yet
            return history;

        //Collect the history
         //
        Stack<URL> backlogBackup = new LinkedListStack<>();
        while(!backlog.isEmpty()){
            backlogBackup.push(backlog.pop());
        }
        //And write it back into backlog and our SinglyLinkedList simultaneously
         //
        while(!backlogBackup.isEmpty()){
            URL visitedPage = backlogBackup.pop();
            backlog.push(visitedPage);
            history.insertFirst(visitedPage);
        }
        history.insertFirst(currentPage);
        return history;
    }

}
