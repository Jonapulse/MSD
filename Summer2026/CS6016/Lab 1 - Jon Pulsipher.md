### Part 1 
1) Grocery store - 
- Inventory `[__SKU(string)__, name(string), quantity(integer), price(real)]`

2) Grocery store v2 (by aisle) - 
- Inventory `[__SKU(string)__, name(string), price(real)]`
- Aisles `[__aisleNum(integer)__, __SKU(string)__]`

3) Car Sales - 
- Stock `[__VIN(string)__, make(string), model(string), year(integer), color(string)]`
- Salespeople `[__SSN(integer)__, name(string)]`
- AssignedSeller `[__VIN(string)__, __SSN(integer)__]`

### Part 2
1) Grocery Store
```
CREATE TABLE Inventory(
	SKU STRING,
	Name STRING,
	Quantity INTEGER,
	Price REAL,
	PRIMARY KEY(SKU)
);
```
2) Grocery store v2 (by aisle)
```
CREATE TABLE Inventory(
	SKU STRING,
	Name STRING,
	Price REAL,
	PRIMARY KEY(SKU)
);
CREATE TABLE Aisles(
	AisleNumber INTEGER,
	SKU STRING,
	PRIMARY KEY(AisleNumber, SKU),
	FOREIGN KEY(SKU) REFERENCES Inventory(ParentSKU)
);
```
3) Car Sales - 
```
CREATE TABLE Stock(
	VIN STRING,
	Make STRING,
	Model STRING,
	Year INTEGER,
	Color STRING,
	PRIMARY KEY(VIN)
);

CREATE TABLE Salespeople(
	SSN INTEGER,
	Name STRING,
	PRIMARY KEY(SSN)
);

CREATE TABLE AssignedSellers(
	VIN STRING,
	SSN INTEGER,
	PRIMARY KEY(VIN, SSN),
	FOREIGN KEY(VIN) REFERENCES Stock(ParentVIN),
	FOREIGN KEY(SSN) REFERENCES Salespeople(ParentSSN)
);
```
### Part 3
**Stock**

| VIN               | Make   | Model   | Year | Color |
| ----------------- | ------ | ------- | ---- | ----- |
| 11111111111111111 | Toyota | Tacoma  | 2008 | Red   |
| 11111111111111112 | Toyota | Tacoma  | 1999 | Green |
| 11111111111111113 | Tesla  | Model 3 | 2018 | White |
| 11111111111111114 | Subaru | WRX     | 2016 | Blue  |
| 11111111111111115 | Ford   | F150    | 2004 | Red   |
**Salespeople**

| SSN       | Name   |
| --------- | ------ |
| 111111111 | Arnold |
| 111111112 | Hanna  |
| 111111113 | Steve  |
**AssignedSellers**

| VIN               | SSN       |
| ----------------- | --------- |
| 11111111111111111 | 111111111 |
| 11111111111111112 | 111111111 |
| 11111111111111111 | 111111112 |
| 11111111111111115 | 111111112 |
| 11111111111111113 | 111111113 |
### Part 4
|A1|A2|A3|
|---|---|---|
|x|4.0|q|
|y|4.0|p|
|z|3.1|p|
|z|4.0|p

| Attribute Sets | Superkey? | Proper Subsets                                 | Key? |
| -------------- | --------- | ---------------------------------------------- | ---- |
| {A1}           | No        | {}                                             | No   |
| {A2}           | No        | {}                                             | No   |
| {A3}           | No        | {}                                             | No   |
| {A1, A2}       | Yes       | {A1}, {A2}                                     | Yes  |
| {A1, A3}       | No        | {A1}, {A3}                                     | No   |
| {A2, A3}       | No        | {A2}, {A3}                                     | No   |
| {A1, A2, A3}   | Yes       | {A1, A2}, {A2, A3}, {A1, A3}, {A1}, {A2}, {A3} | No   |
### Part 5
1) If {x} is a superkey, then any set containing x is also a superkey.
	**Yes**, because combining unique rows with non-unique rows does not make the unique rows less unique.
2) If {x} is a key, then any set containing x is also a key.
	**No**, because a key cannot contain a subset that is also a key (or superkey).
3) If {x} is a key, then {x} is also a SuperKey.
	**Yes,** because 'key' is defined by the same uniqueness criteria that defines SuperKey plus some others.
4) If {x, y, z} is a superkey, then one of {x}, {y}, or {z} must also be a superkey.
	**No,** because a table must have a key, but it could be composed by unique combinations of non-unique rows: {1,1,2}, {1,2,2}, {2,2,3}.
5) If an entire schema consists of the set {x, y, z}, and if none of the proper subsets of {x, y, z} are keys, then {x, y, z} must be a key.
	**Yes,**  because a table by definition must have a key, and none of the other candidates are keys.