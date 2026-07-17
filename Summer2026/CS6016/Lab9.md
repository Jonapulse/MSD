### Part 1 - Selecting Indexes
1) Former Employees: **Start Date + End Date multi-column index.**
	- *After certain date?* With a Start Date index you can quickly find employees that started on and after a target date.
	- *After + working until?* With an End Date index you can quickly find employees that ended on or after a target date. You can then find overlap between the groups who started started after date 1 and ended after date 2.
2) Grades: **Grade index is sufficient.** ~~+ Class Name multi-column index.~~
	- *B or better?* With a grade part of multi-column index you can quickly find all Bs and higher.
	- *All classes where a student earned a D?* Because our primary key includes class name, we are quickly able to collect class names from just our grade index. 
3) Grades again: **Class Name + Grade multi-column index.**
	- *All classes ordered by class name?* With the class name part of your index you can get sorted classnames. The sorted nature of that information may allow you to skip reading every row (if it's worth going to that trouble).
	- *All students who earned an 'A' in a certain class?* With the Class Name + Grade index you can quickly find the class and the range of students with As.
4) Chess: **Elo index for Players.**
	- `select Name from Players where Elo >=2050;` With an Elo index you can quickly find Players with >=2050 elo. 
	- `select Name, gID from Player join Games where pID=WhitePlayer;` It seems like the minimum number of steps to execute this query is printing a row for every game, so we want to be able to quickly get the player row associated with the White Player id. Our pid primary key index already supports that.
5) Library: **None.**
	- `select * from Inventory natural join CheckedOut;` We need to loop through all rows in CheckedOut so no index will speed that up, and Inventory is already indexed on s\d derial, which each CheckedOut row has.
6) More library queries: **Cardnum index on CheckedOut**
	- `select * from Inventory natural join CheckedOut where CardNum=2;` The cardnum index allows quick lookup for checkedOut rows, and those have serial, which Inventory is already indexed on.
	- `select * from Patrons natural join CheckedOut;` The cardnum index allows quick lookup for checkedOut rows, and Patrons is already indexed on cardnum, its primary key.
7) Still more library queries: **ISBN index on inventory.**
```
var query = db.Titles.Select( t => new {
	title = t.Title,
	Serial = t.SerialNavigation.toList()
});
```
- We loop through all titles so can't speed that up. ISBN index on inventory let us quickly find the serials attached to that title.

### Part 2 - B+ Tree Index Structures
1) Students table
	- *How many rows in the first leaf node before split?* At 15 bytes per row we can fit **273 rows** with 1 byte leftover.
	- *What is the max number of keys stored in an internal node of the primary index?* Our primary index is student id + classname which sums to 14 bytes. **292 keys** can fit.
	- *What is the maximum number of rows in the table if primary index has a height of 1?* (292 + 1) branches * 273 rows = **79,989 max rows**.
	- *What is the minimum number of rows in the table if the primary index has a height of 1?* Our root node can be as small one key which will branch into 2 child nodes, which must be at least half full at 137. So 2 * 137 = **274 rows.**
	- *If there is a secondary index on grade, what is the max number of entries a leaf node can hold in the secondary index?* The "pointer" back to our primary index is the 14-byte primary key, and the value it is attached to is our 1 byte grade. Our 4096-byte leaf can fit **273 entries**, same as our primary index leaves because both end up storing the full row.
2) Another table
	- *What is max number of leaf nodes in the primary index if the table contains 48 rows?* The 4096 table fits 32 rows of 128 byte length. The minimum number would be two nodes. Three leaf nodes filled with 16 rows would still be half-full: so, **3**.
	- *What is the minimum number of leaf nodes in the primary index if the table contains 48 rows?* **2**.