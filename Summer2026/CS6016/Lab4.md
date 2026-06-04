## Part 3
1) `SELECT title FROM titles WHERE author = '<author>';`
2) `SELECT serial FROM titles NATURAL JOIN inventory WHERE author = '<author>';`
3) `SELECT title FROM checkedout NATURAL JOIN inventory NATURAL JOIN checkedout NATURAL JOIN patrons WHERE name = '<name>';`
4) `SELECT DISTINCT phone FROM phones NATURAL JOIN checkedout;`
## Part 4
1) SELECT name FROM players WHERE elo >= 2850;
2) SELECT DISTINCT name FROM players p JOIN games g ON p.pid = g.whiteplayer; //(LIMIT 50 to not explode)
3) SELECT DISTINCT name FROM players p JOIN games g ON p.pid = g.whiteplayer AND g.result = 'W';  //(LIMIT 50 to not explode)
4) 
```
	//My original
	SELECT p.name FROM players p JOIN (SELECT * FROM games NATURAL JOIN (SELECT * FROM events WHERE date >= '2018-01-01' AND date <= '2018-12-31')) g ON p.pid = g.whiteplayer OR p.pid = g.blackplayer; //(LIMIT 50 to not explode)
	
	//Cleaner "Common Table Expression" re-write without natural joins
	WITH TargetEvents AS (
		SELECT eid
		FROM events
		WHERE date >= '2018-01-01' AND date <= '2018-12-31'
	),
	TargetGames AS(
		SELECT g.whiteplayer, g.blackplayer
		FROM games g
		JOIN TargetEvents t ON g.eid = t.eid
	)
	SELECT DISTINCT p.name
	FROM players p
	JOIN TargetGames tg
	ON p.pid = tg.whiteplayer OR p.pid = tg.blackplayer;
	//LIMIT 50; to not explode
```
5) 
```
WITH LostGames AS(
	SELECT *
	FROM games g
	JOIN players p ON (p.pid = g.whiteplayer AND p.name = "Carlsen, Magnus" AND g.result="B") OR (p.pid = g.blackplayer AND p.name = "Carlsen, Magnus" AND g.result="W")
)
SELECT name, date
FROM events e JOIN LostGames lg ON e.eid = lg.eid;
```
6) 
```
WITH MagnusBlackOpponents AS(
	SELECT g.blackplayer AS pid
	FROM games g
	JOIN players p ON g.whiteplayer = p.pid
	WHERE p.name = 'Carlsen, Magnus'
),
MagnusWhiteOpponents AS(
	SELECT g.whiteplayer AS pid
	FROM g
	JOIN p ON g.blackplayer = p.pid
	WHERE p.name = 'Carlsen, Magnus'
)
SELECT name FROM players p JOIN (
	SELECT pid FROM MagnusBlackOpponents
	UNION
	SELECT pid FROM MagnusWhiteOpponents)
) AS combinedOpponents
ON p.pid = combinedOpponents.pid;
```