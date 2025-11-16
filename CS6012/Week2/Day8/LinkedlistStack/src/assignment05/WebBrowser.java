package assignment05;

import java.net.URL;
import java.util.NoSuchElementException;

public class WebBrowser {
    //TODO: Analyze whether to use ArrayList stack or LinkedList stack and use the more appropriate
    Stack<URL> backlog = new LinkedListStack<>();
    URL current = null;
    Stack<URL> frontlog = new LinkedListStack<>();;

    public WebBrowser() {}

    public WebBrowser(SinglyLinkedList<URL> history){
        current = history.deleteFirst();
        history.deleteFirst();
        while(!history.isEmpty()){
            backlog.push(history.deleteFirst());
        }
    }

    public void visit(URL webpage){
        frontlog.clear();
        backlog.push(current);
        current = webpage;
    }

    public URL back() throws NoSuchElementException {
        if(backlog.isEmpty())
            throw new NoSuchElementException();

        frontlog.push(current);
        current = backlog.pop();
        return current;
    }

    public URL forward() throws NoSuchElementException {
        if(frontlog.isEmpty())
            throw new NoSuchElementException();
        backlog.push(current);
        current = frontlog.pop();
        return current;
    }

    public SinglyLinkedList<URL> history() {
        SinglyLinkedList<URL> history = new SinglyLinkedList<>();
        Stack<URL> backlogBackup = new LinkedListStack<>();

        //Collect the history
         //
        backlogBackup.push(backlog.pop());
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
        return history;
    }

}
