#### Intermediate Retrieval Queries
- *Find the Titles of the library's oldest `<N>` books. Assume the lowest serial number is the oldest book.*
```
SELECT title FROM titles NATURAL JOIN inventory ORDER BY serial LIMIT <N>;
```
- *Find the name of the person who has checked out the most recent book. Assume the highest serial number is the newest book. Hint: the highest serial number book may not be checked out by anyone.*
```
SELECT name FROM patrons NATURAL JOIN checkedout ORDER BY serial DESC LIMIT 1;
```
- *Find the phone number(s) of anyone who has not checked out any books.*
```
SELECT phone from phones WHERE cardnum NOT IN (select cardnum from checkedout);
```
- *The library wants to expand the number of unique selections in its inventory, thus, it must know the ISBN and Title of all books that it owns at least one copy of. Create a query that will return the ISBN and Title of every book in the library, but will not return the same book twice.*
```
SELECT DISTINCT ISBN, title FROM titles NATURAL JOIN inventory;
```
#### Advanced Retrieval Queries
- *Find the name of the patron who has checked out the most books.*
```
SELECT name FROM patrons NATURAL JOIN checkedout group by cardnum;
```
- *Find the Authors who have written more than one book. Assume that two Authors with the same name are the same Author for this query.*
```
SELECT name FROM (SELECT name, COUNT(serial) from patrons NATURAL JOIN checkedout GROUP BY cardnum ORDER BY count DESC) LIMIT 1;
```
- *Find the Authors for which the library has more than one book in inventory (this includes multiple copies of the same book). Assume that two Authors with the same name are the same Author for this query.*
```
WITH titleInv AS(SELECT * FROM inventory NATURAL JOIN titles) SELECT DISTINCT t1.author FROM titleInv t1 CROSS JOIN titleInv t2 WHERE t1.author = t2.author AND t1.serial > t2.serial;
```

#### A couple more queries
- *The library wants to implement a customer loyalty program based on how many books each patron has checked out. Provide an SQL query that returns the names, number of books they have checked out, and loyalty level of each Patron. The loyalty level should be the string "Platinum" if they have checked out > 2 books, "Gold" if they have 2 books, "Silver" if they have 1 book, and "Bronze" if they have no books. Hint: remember that NULL represents an unknown in SQL (it does not represent 0).*
```
WITH patronRecord AS (SELECT name, COALESCE(COUNT(serial), 0) bookCount FROM patrons NATURAL LEFT JOIN checkedout GROUP BY cardnum)
SELECT name, bookCount, CASE
	WHEN bookCount > 2 THEN 'Platinum'
	WHEN bookCount = 2 THEN 'Gold'
	WHEN bookCount = 1 THEN 'Silver'
	ELSE 'Bronze'
END
FROM patronRecord;
```
- *Find the name of the oldest book by each author. By oldest, we mean the book with the smallest serial number.*
```
SELECT title from (titles NATURAL JOIN inventory) NATURAL JOIN (SELECT MIN(serial), author FROM titles NATURAL JOIN inventory GROUP BY author) WHERE serial = min;
```