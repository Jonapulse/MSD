package assignment02;

import java.util.GregorianCalendar;

public class LibraryBook extends Book {

    ///Fields holder and dueDate are null when the book is not checked out
    String holder = null;
    GregorianCalendar dueDate = null;

    public LibraryBook(long isbn, String author, String title) {
        super(isbn, author, title);
    }

    public String getHolder() {
        return holder;
    }

    public GregorianCalendar getDueDate() {
        return dueDate;
    }
    public void checkOut(String holder, GregorianCalendar dueDate) {
        this.holder = holder;
        this.dueDate = dueDate;
    }

    public void checkIn() {
        this.holder = null;
        this.dueDate = null;
    }
}
