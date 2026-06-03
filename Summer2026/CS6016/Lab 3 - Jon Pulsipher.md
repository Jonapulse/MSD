### Part 1 - Joins
1. $T1 \bowtie_{T1.A = T2.A} T2$

| A   | Q   | R   | A   | B   | C   |
| --- | --- | --- | --- | --- | --- |
| 20  | a   | 5   | 20  | b   | 6   |
| 20  | a   | 5   | 20  | b   | 5   |

2. $T1 \bowtie_{T1.Q = T2.B} T2$

| A   | Q   | R   | A   | B   | C   |
| --- | --- | --- | --- | --- | --- |
| 25  | b   | 8   | 20  | b   | 6   |
| 25  | b   | 8   | 20  | b   | 5   |

3. $T1 \bowtie T2$

| A   | Q   | R   | B   | C   |
| --- | --- | --- | --- | --- |
| 20  | a   | 5   | b   | 6   |
| 20  | a   | 5   | b   | 5   |

4. $T1 \bowtie_{T1.A = T2.A \land T1.R = T2.C} T2$

| A   | Q   | R   | A   | B   | C   |
| --- | --- | --- | --- | --- | --- |
| 20  | a   | 5   | 20  | b   | 5   |
### Part 2 - Chess Queries
1. $\pi_{Name}(\sigma_{Elo >= 2850}(Players))$
2. $\pi_{Name}(Players\bowtie_{Players.pID = Games.wpID}Games)$
3. $\pi_{Name}(Players\bowtie_{Players.pID = Games.wpID}\sigma_{Result=1-0}(Games))$
4. $\pi_{Name}(Players\bowtie_{Players.pID=Games.wpID \lor Players.pID=Games.bpID}Games\bowtie(\sigma_{Year = 2018}(Events)))$
5. 
$\rho(tPlayer, \sigma_{Name = "Magnus Carlsen"}(Players))$

$\rho(lostAsWhite, \sigma_{Result="0-1"}(Games\bowtie_{tPlayer.pID=Games.wpID}tPlayer))$

$\rho(lostAsBlack, \sigma_{Result="1-0"}(Games\bowtie_{tPlayer.pID=Games.bpID}tPlayer))$

$\pi_{Name, Year}(Events \bowtie \pi_{eID}(lostAsWhite \cup lostAsBlack))$

6. 
$\rho(tPlayer, \sigma_{Name = "Magnus Carlsen"}(Players))$

$\rho(whiteOpponents, \pi_{wID}(Games\bowtie_{tPlayer.pID=Games.bID}tPlayer))$

$\rho(blackOpponents, \pi_{bID}(Games\bowtie_{tPlayer.pID=Games.wID}tPlayer))$

$\rho(allOpponents, \pi_{wID \rightarrow pID}(whiteOpponents) \cup \pi_{bID \rightarrow pID}(blackOpponents))$

$\pi_{Name}(allOpponents \bowtie Players)$
### Part 3 - LMS Queries
##### 3.1:
a) 
$\rho(C, \pi_{sid}(\sigma_{Grd=C}(Enrolled)))$
$\pi_{Name}((\pi_{sid}(Enrolled) - C) \bowtie Students)$

| Name     |
| -------- |
| Hermione |
| Harry    |

b) Find the names of enrolled students who have never earned a C.
##### 3.2:
a)
$\rho(S1, Students)$
$\rho(S2, Students)$
$\pi_{S2.Name}(\sigma_{S1.Name == Ron \wedge S1.DOB == S2.DOB \wedge S2.name != Ron}(S1 \times S2))$

| Name     |
| -------- |
| Hermione |

b) Find the names of students who share a DOB with Ron (and don't include his name).

##### 3.3:
$\pi_{Name}((\pi_{cid,sid}(Enrolled) /\pi_{sid}(Students))\bowtie Courses)$

| Name    |
| ------- |
| {empty} |

b) Find the names of the courses where every student (in the Students table) are enrolled.

### Part 4
$\pi_{Name}(Students\bowtie\pi_{sID,cID}(Enrolled)/\pi_{cID}(\sigma_{cID>=3000 \land cID<4000}(Courses)))$