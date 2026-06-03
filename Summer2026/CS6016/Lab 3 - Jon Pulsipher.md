### To-do
- What to do today?
	- HW and knock out a bunch of those applications?

### Part1 - Joins
### T1

| A   | Q   | R   |
| --- | --- | --- |
| 20  | a   | 5   |
| 25  | b   | 8   |
| 35  | a   | 6   |

### T2

| A   | B   | C   |
| --- | --- | --- |
| 20  | b   | 6   |
| 45  | c   | 3   |
| 20  | b   | 5   |
1. $T1 \bowtie_{T1.A = T2.A} T2$
2. $T1 \bowtie_{T1.Q = T2.B} T2$
3. $T1 \bowtie T2$
4. $T1 \bowtie_{T1.A = T2.A \wedge T1.R = T2.C} T2$

### Part 2 - Chess Queries
### Events

|Name|Year|eID|
|---|---|---|
|World Championship|1987|1|
|Moscow Open|2018|2|
|World Championship|2018|3|

### Players

|Name|Elo|pID|
|---|---|---|
|Magnus Carlsen|2882|1|
|Judit Polgar|2735|2|
|Fabiano Caruana|2844|3|
|Gary Kasparov|2851|4|
|Anatoly Karpov|2780|5|

### Games: wpID (white) and bpID (black) reference pID from Players

|gID|eID|Result|wpID|bpID|
|---|---|---|---|---|
|1|3|1/2-1/2|1|3|
|2|3|1/2-1/2|3|1|
|3|2|1-0|2|1|
|4|1|1/2-1/2|4|5|
|5|3|0-1|3|1|
1. Find the names of any player with an Elo rating of 2850 or higher.
2. Find the names of any player who has ever played a game as white.
3. Find the names of any player who has ever won a game as white.
4. Find the names of any player who played any games in 2018.
5. Find the names and dates of any event in which Magnus Carlsen lost a game.
6. Find the names of all opponents of Magnus Carlsen. An opponent is someone who he has played a game against. Hint: Both Magnus and his opponents could play as white or black.

## Part 3 - LMS Queries

#### Part 3.1: 
a) Provide the relation that is the result of the following query. Your relation should be in the form of a table, and should include the schema.

$\rho(C, \pi_{sid}(\sigma_{Grd=C}(Enrolled)))$

Name((πsid(Enrolled)−C)⋈Students)

b) Provide a simple English description of what the query is searching for. Your description should be in general terms (remember that the original LMS instance data may change).

#### Part 3.2:
a) Provide the relation that is the result of the following query. Your relation should be in the form of a table, and should include the schema.

$\rho(S1, Students)$

$\rho(S2, Students)$

$\pi_{S2.Name}(\sigma_{S1.Name == Ron \wedge S1.DOB == S2.DOB \wedge S2.name != Ron}(S1 \times S2))$

b) Provide a simple English description of what the query is searching for. Your description should be in general terms (remember that the original LMS instance data may change).

#### Part 3.3:
a) Provide the relation that is the result of the following query. Your relation should be in the form of a table, and should include the schema.

πName((πcid,sid(Enrolled)/πsid(Students))⋈Courses)

b) Provide a simple English description of what the query is searching for. Your description should be in general terms (remember that the original LMS instance data may change).

#### Part 4:
Provide a relational algebra query that uses the divide operator to find the names of all students who are taking all of the 3xxx-level classes.