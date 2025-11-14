package assignment02;

import java.io.File;
import java.io.FileNotFoundException;
import java.text.ParseException;
import java.util.ArrayList;
import java.util.GregorianCalendar;
import java.util.Scanner;

/**
 * Class representation of a library (a collection of library books).
 *
 */
public class Library <T> {

    private ArrayList<LibraryBook> library;

    public Library() {
        library = new ArrayList<LibraryBook>();
    }

    /**
     * Add the specified book to the library, assume no duplicates.
     *
     * @param isbn   -- ISBN of the book to be added
     * @param author -- author of the book to be added
     * @param title  -- title of the book to be added
     */
    public void add(long isbn, String author, String title) {
        library.add(new LibraryBook(isbn, author, title));
    }

    /**
     * Add the list of library books to the library, assume no duplicates.
     *
     * @param list -- list of library books to be added
     */
    public void addAll(ArrayList<LibraryBook<T>> list) {
        library.addAll(list);
    }

    /**
     * Add books specified by the input file. One book per line with ISBN, author,
     * and title separated by tabs.
     * <p>
     * If file does not exist or format is violated, do nothing.
     *
     * @param filename
     */
    public void addAll(String filename) {
        ArrayList<LibraryBook<T>> toBeAdded = new ArrayList<LibraryBook<T>>();

        try (Scanner fileIn = new Scanner(new File(filename))) {

            int lineNum = 1;

            while (fileIn.hasNextLine()) {
                String line = fileIn.nextLine();

                try (Scanner lineIn = new Scanner(line)) {
                    lineIn.useDelimiter("\\t");

                    if (!lineIn.hasNextLong()) {
                        throw new ParseException("ISBN", lineNum);
                    }
                    long isbn = lineIn.nextLong();

                    if (!lineIn.hasNext()) {
                        throw new ParseException("Author", lineNum);
                    }
                    String author = lineIn.next();

                    if (!lineIn.hasNext()) {
                        throw new ParseException("Title", lineNum);
                    }
                    String title = lineIn.next();
                    toBeAdded.add(new LibraryBook<T>(isbn, author, title));
                }
                lineNum++;
            }
        } catch (FileNotFoundException e) {
            System.err.println(e.getMessage() + " Nothing added to the library.");
            return;
        } catch (ParseException e) {
            System.err.println(e.getLocalizedMessage() + " formatted incorrectly at line " + e.getErrorOffset()
                    + ". Nothing added to the library.");
            return;
        }

        library.addAll(toBeAdded);
    }

    /**
     * Returns the holder of the library book with the specified ISBN.
     * <p>
     * If no book with the specified ISBN is in the library, returns null.
     *
     * @param isbn -- ISBN of the book to be looked up
     */
    public T lookup(long isbn) {
        for (LibraryBook<T> book : library) {
            if (isbn == book.getIsbn()) {
                return book.getHolder();
            }
        }
        return null;
    }

    /**
     * Returns the list of library books checked out to the specified holder.
     * <p>
     * If the specified holder has no books checked out, returns an empty list.
     *
     * @param holder -- holder whose checked out books are returned
     */
    public ArrayList<LibraryBook<T>> lookup(T holder) {
        ArrayList<LibraryBook<T>> checkedOutList = new ArrayList<>();
        for (LibraryBook<T> book : library) {
            T checkedOutBy = book.getHolder();
            if (checkedOutBy != null && checkedOutBy.equals(holder))
                checkedOutList.add(book);
        }
        return checkedOutList;
    }

    /**
     * Returns book matching isbn or null if not found
     *
     * @param isbn --
     * @return LibraryBook with matching isbn
     */
    public LibraryBook<T> lookupBook(long isbn) {
        for (LibraryBook<T> book : library) {
            if (book.getIsbn() == isbn)
                return book;
        }
        return null;
    }

    /**
     * Sets the holder and due date of the library book with the specified ISBN.
     * <p>
     * If no book with the specified ISBN is in the library, returns false.
     * <p>
     * If the book with the specified ISBN is already checked out, returns false.
     * <p>
     * Otherwise, returns true.
     *
     * @param isbn   -- ISBN of the library book to be checked out
     * @param holder -- new holder of the library book
     * @param month  -- month of the new due date of the library book
     * @param day    -- day of the new due date of the library book
     * @param year   -- year of the new due date of the library book
     *
     */
    public boolean checkout(long isbn, T holder, int month, int day, int year) {
        LibraryBook<T> book = lookupBook(isbn);
        if (book == null || book.getHolder() != null)
            return false;
        book.checkOut(holder, new GregorianCalendar(year, month, day));
        return true;
    }

    /**
     * Unsets the holder and due date of the library book.
     * <p>
     * If no book with the specified ISBN is in the library, returns false.
     * <p>
     * If the book with the specified ISBN is already checked in, returns false.
     * <p>
     * Otherwise, returns true.
     *
     * @param isbn -- ISBN of the library book to be checked in
     */
    public boolean checkin(long isbn) {
        LibraryBook<T> book = lookupBook(isbn);
        if (book == null || book.getHolder() == null)
            return false;
        book.checkIn();
        return true;
    }

    /**
     * Unsets the holder and due date for all library books checked out be the
     * specified holder.
     * <p>
     * If no books with the specified holder are in the library, returns false;
     * <p>
     * Otherwise, returns true.
     *
     * @param holder -- holder of the library books to be checked in
     */
    public boolean checkin(T holder) {
        ArrayList<LibraryBook<T>> checkedOutList = lookup(holder);
        if(checkedOutList == null || checkedOutList.isEmpty())
            return false;
        for(LibraryBook<T> book : lookup(holder))
            book.checkIn();
        return true;
    }
}
