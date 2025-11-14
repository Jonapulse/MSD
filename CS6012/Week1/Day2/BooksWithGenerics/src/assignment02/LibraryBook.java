package assignment02;

import java.util.GregorianCalendar;

public class LibraryBook<T> extends Book {

    ///Fields holder and dueDate are null when the book is not checked out
    T holder = null;
    GregorianCalendar dueDate = null;

    public LibraryBook(long isbn, String author, String title) {
        super(isbn, author, title);
    }

    public T getHolder() {
        return holder;
    }

    public GregorianCalendar getDueDate() {
        return dueDate;
    }
    public void checkOut(T holder, GregorianCalendar dueDate) {
        this.holder = holder;
        this.dueDate = dueDate;
    }

    public void checkIn() {
        this.holder = null;
        this.dueDate = null;
    }
}
