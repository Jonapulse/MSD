## Ultimate Frisbee FDs

##### Design a DB schema for Fantasy Ultimate Frisbee League following BCNF

**Attributes:** PlayerID, GameID, TeamID, FantasyTeamID, Score, Assist, Block, Turnover, WeekNumber
**Monster table:** P, G, Ti, Fti, S, A, B, Tu, W
**Fantasy Score FDs**: S, A, B, Tu, W -> Fantasy Score (Not an FD b/c Fantasy Score is a not an attribute)
P, G -> S, A, B, Tu, W - These are per-player, per-game values (so player made 6 scores, 2 assists, 1 block, 1 turnover, etc)
P -> Ti

**P**, **G**, S, A, B, Tu, W - (P,G) is a key. 
P, **Ti** - (Ti) is key
P, **Fti** - (Fti) is key

This gives us three tables. Two of them are simple player lists for real and fantasy teams. The other is a less intuitive list of player contributions to games that doesn't give a clear picture of who played in or won the games, though that information is all calculable.

This table setup does not store the score of a game as a separate attribute. Whether a player gets a bonus point for being in a winning game is calculated based on number of scores made by all players in that game and the team they belong to. 
##### How does this approach compare to an ER Diagram-first approach?

We would group entities, their attributes, and their relationships. Something like...
- Entities: Players, Games, Teams, Fantasy Teams
- Relationships: BelongsToReal, BelongsToFantasy, PlayedIn

Following this approach I would be inclined to include scores in the games table, and I might find it necessary to add an additional table to track player contributions to games. The ER diagram and resulting tables would be more readable than the FD setup I put together, but would add extra tables and attributes that aren't strictly necessary.