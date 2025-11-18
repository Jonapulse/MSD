package assignment02;

import java.util.GregorianCalendar;

public class LibraryBook<T> extends Book {

    ///Fields holder and dueDate are null when the book is not checked out
    T holder = null;
    GregorianCalendar dueDate = null;

    public LibraryBook(long isbn, String author, String title) {
        super(isbn, author, title);
    }

    /**
     * Returns holder. Expected T are String name, String, email, or PhoneNumber #.
     * @return
     */
    public T getHolder() {
        return holder;
    }

    /**
     * @return dueDate as Gregorian Calendar
     */
    public GregorianCalendar getDueDate() {
        return dueDate;
    }

    /**
     * "checks out" this book, setting a holder and due date.
     * @param holder
     * @param dueDate
     */
    public void checkOut(T holder, GregorianCalendar dueDate) {
        this.holder = holder;
        this.dueDate = dueDate;
    }

    /**
     * resets holder and due date to null. Library recognize books with null holders
     * as "checked out".
     */
    public void checkIn() {
        this.holder = null;
        this.dueDate = null;
    }
}
