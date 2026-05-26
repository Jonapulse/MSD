### ER Diagram
![diagram](./Lab_2_ER_Diagram.png)
### Schemas
Player(player_id (serial) PK, player_name (varchar(255), player_elo (small_int))

Event(event_date (date) PK, event_name (varchar(255) PK, event_site (varchar(255)))

Game(game_round (serial) PK, white_player_id (integer) FK -> Player, black_player_id (integer) FK -> Player), result (varchar(7)), movelist (varchar(1000)))

### SQL Commands

```
CREATE TABLE Player(
	player_id SERIAL,
	player_name VARCHAR(255),
	player_elo SMALLINT,
	PRIMARY KEY(player_id)
);

CREATE TABLE Event(
	event_date DATE,
	event_name VARCHAR(255),
	event_site VARCHAR(255),
	PRIMARY KEY(event_date, event_name)
);

CREATE TABLE GAME(
	game_round SERIAL,
	white_player_id INTEGER,
	black_player_id INTEGER,
	game_event_name VARCHAR(255),
	game_event_date DATE,
	result VARCHAR(7), //"1/2-1/2" is 7 chars long
	movelist VARCHAR(1000),
	PRIMARY KEY(game_round, white_player_id, black_player_id),
	FOREIGN KEY(white_player_id) REFERENCES Player(player_id),
	FOREIGN KEY(black_player_id) REFERENCES Player(player_id)
	FOREIGN KEY (game_event_name, game_event_date) REFERENCES Event(event_name, event_date)
);
```
