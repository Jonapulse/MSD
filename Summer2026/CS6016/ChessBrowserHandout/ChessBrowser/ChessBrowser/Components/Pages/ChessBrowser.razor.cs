using System.Diagnostics;
using Microsoft.AspNetCore.Components.Forms;
using Npgsql;
using NpgsqlTypes;
using System.Text.RegularExpressions;

namespace ChessBrowser.Components.Pages
{
    public partial class ChessBrowser
    {
        /// <summary>
        /// Bound to the Unsername form input
        /// </summary>
        private string Username = "";

        /// <summary>
        /// Bound to the Database form input
        /// </summary>
        private string Database = "";

        /// <summary>
        /// Represents the progress percentage of the current
        /// upload operation. Update this value to update 
        /// the progress bar.
        /// </summary>
        private int    Progress = 0;

        private ChessData fullPgnData;

        private record struct Game (
            string round, 
            string result, 
            string moves, 
            string blackPlayerName, //key for bPid lookup
            string whitePlayerName, //key for wPid lookup
            string eventName, //identifiers for eid lookup
            string eventSite,
            string eventDate
        );

        private record struct ChessEvent(
            string name,
            string site,
            string date,
            int eid
        );

        private record struct Player(
            string name,
            string elo,
            int pid
        );

        private record struct ChessData(
            Dictionary<string, Player> players, //Keyed on player name
            Dictionary<string, ChessEvent> events,
            Dictionary<string, Game> games
        );
    
        /// <summary>
        /// This method runs when a PGN file is selected for upload.
        /// Given a list of lines from the selected file, parses the 
        /// PGN data, and uploads each chess game to the user's database.
        /// </summary>
        /// <param name="PGNFileLines">The lines from the selected file</param>
        private async Task InsertGameData(string[] PGNFileLines)
        {
            string connectionString = GetConnectionString();
      
            //wrap this in try/catch with exception printing so the UI doesn't swallow your exceptions
            try
            {
                //Parse Data
                ChessData data = ParseChessData(PGNFileLines);
        
                //Upload Data
                Progress = 0;
                int uploadSum = 0;
                int uploadTarget = data.events.Count + data.players.Count + data.games.Count;

                await using var dataSource =
                    NpgsqlDataSource.Create(connectionString);
                await using var commandMakeEventTable =
                    dataSource.CreateCommand(
                        """
                        CREATE TABLE IF NOT EXISTS events(
                            name VARCHAR(255), 
                            site VARCHAR(255), 
                            date DATE, 
                            eid SERIAL, 
                            PRIMARY KEY(eid),
                            CONSTRAINT unique_event UNIQUE(name, site, date)
                        );
                        """);
                await using var commandMakePlayerTable =
                    dataSource.CreateCommand(
                        """
                        CREATE TABLE IF NOT EXISTS players(
                            name VARCHAR(255), 
                            elo INTEGER, 
                            pid SERIAL, 
                            PRIMARY KEY(pid),
                            CONSTRAINT unique_player UNIQUE(name)
                        );
                        """);
                    await using var commandMakeGameTable =
                    dataSource.CreateCommand(
                        """
                        CREATE TABLE IF NOT EXISTS games(
                            round VARCHAR(10), 
                            result CHAR(1), 
                            moves VARCHAR(2000), 
                            blackplayer INTEGER, 
                            whiteplayer INTEGER, 
                            eid INTEGER, 
                            PRIMARY KEY(eid, round, blackplayer, whiteplayer), 
                            FOREIGN KEY(eid) REFERENCES events(eid),
                            FOREIGN KEY(blackplayer) REFERENCES players(pid),
                            FOREIGN KEY(whiteplayer) REFERENCES players(pid)
                        );
                        """);

                await commandMakeEventTable.ExecuteNonQueryAsync();
                await commandMakePlayerTable.ExecuteNonQueryAsync();
                await commandMakeGameTable.ExecuteNonQueryAsync();
                
                //Insert events
                foreach(ChessEvent pgnEvent in data.events.Values)
                {
                    await using var insertCommand = dataSource.CreateCommand(
                        "INSERT INTO events (name, site, date) VALUES(@name,@site,@date) " +
                        "ON CONFLICT (name, site, date) DO UPDATE SET name = EXCLUDED.name RETURNING eid");
                    insertCommand.Parameters.AddWithValue("name", pgnEvent.name);
                    insertCommand.Parameters.AddWithValue("site", pgnEvent.site);
                    insertCommand.Parameters.AddWithValue("date", NpgsqlTypes.NpgsqlDbType.Date, DateTime.Parse(pgnEvent.date.Replace('.', '-'))); //PostgreSQL's Date wants '-'

                    var result = await insertCommand.ExecuteScalarAsync();
                    if (result != null)
                    {
                        string key = pgnEvent.name + pgnEvent.site + pgnEvent.date;
                        ChessEvent updatedEvent = data.events[key];
                        updatedEvent.eid = (int)result;
                        data.events[key] = updatedEvent;
                    }

                    //Update progress
                    uploadSum++;
                    int newProgress = (int)((float)uploadSum / uploadTarget * 100);
                    if (Progress != newProgress)
                    {
                        Progress = newProgress;
                        await InvokeAsync(StateHasChanged);
                    }
                }
                
                //Insert Players
                foreach(Player pgnPlayer in data.players.Values)
                {
                    await using var insertCommand = dataSource.CreateCommand(
                        "INSERT INTO players (name, elo) VALUES(@name,@elo) " +
                        "ON CONFLICT (name) DO UPDATE SET name = EXCLUDED.name RETURNING pid");
                    insertCommand.Parameters.AddWithValue("name", pgnPlayer.name);
                    insertCommand.Parameters.AddWithValue("elo", int.Parse(pgnPlayer.elo));

                    var result = await insertCommand.ExecuteScalarAsync();
                    if (result != null)
                    {
                        string key = pgnPlayer.name;
                        Player updatedEvent = data.players[key];
                        updatedEvent.pid = (int)result;
                        data.players[key] = updatedEvent;
                    }

                    //Update progress
                    uploadSum++;
                    int newProgress = (int)((float)uploadSum / uploadTarget * 100);
                    if (Progress != newProgress)
                    {
                        Progress = newProgress;
                        await InvokeAsync(StateHasChanged);
                    }
                }

                //Insert games
                foreach(Game pgnGame in data.games.Values)
                {
                    await using var insertCommand = dataSource.CreateCommand(
                        "INSERT INTO games (round, result, moves, blackplayer, whiteplayer, eid) " + 
                        "VALUES(@round, @result, @moves, @blackplayer, @whiteplayer, @eid) " +
                        "ON CONFLICT (round, blackplayer, whiteplayer, eid)  DO NOTHING");
                    insertCommand.Parameters.AddWithValue("round", pgnGame.round);
                    insertCommand.Parameters.AddWithValue("result",
                        pgnGame.result == "1-0" ? 'W' : pgnGame.result == "0-1" ? 'B' : 'D');
                    insertCommand.Parameters.AddWithValue("moves", pgnGame.moves);
                    insertCommand.Parameters.AddWithValue("blackplayer", data.players[pgnGame.blackPlayerName].pid);
                    insertCommand.Parameters.AddWithValue("whiteplayer", data.players[pgnGame.whitePlayerName].pid);
                    insertCommand.Parameters.AddWithValue("eid", data.events[GetEventKey(pgnGame.eventName, pgnGame.eventSite, pgnGame.eventDate)].eid);

                    await insertCommand.ExecuteNonQueryAsync();

                    //Update progress
                    uploadSum++;
                    int newProgress = (int)((float)uploadSum / uploadTarget * 100);
                    if (Progress != newProgress)
                    {
                        Progress = newProgress;
                        await InvokeAsync(StateHasChanged);
                    }
                }
            }
            catch (Exception e)
            {
                Console.WriteLine("uh oh: " + e.Message + e.StackTrace);
                throw;
            }
        }

        /// <summary>
        /// Steps through pgn, adding values and movelists into ChessData object for return
        /// </summary>
        /// <param name="PGNFileLines"></param>
        /// <returns>ChessData object</returns>
        private ChessData ParseChessData(string[] PGNFileLines)
        {
            fullPgnData = new ChessData()
            {
                players = new Dictionary<string, Player>(),
                events = new Dictionary<string, ChessEvent>(),
                games = new Dictionary<string, Game>()
            };
            var gameData = new Dictionary<string, string>();
            string gameMoveList = "";
            bool parsedBreak = false;
            foreach (string PGNFileLine in PGNFileLines)
            {
                if (PGNFileLine == "")
                {
                    if (!parsedBreak) 
                    {
                        parsedBreak = true;
                    }
                    else //Game Data End
                    {
                        RecordGameData(fullPgnData, gameData, gameMoveList);
            
                        //Reset per-game data
                        gameData = new Dictionary<string, string>();
                        gameMoveList = "";
                        parsedBreak = false;
                    }
                }
                else if (PGNFileLine[0] == '[') //Value line
                {
                    string label =  PGNFileLine.Substring(1, PGNFileLine.IndexOf(' ') - 1);
                    string value = Regex.Match(PGNFileLine, @"(?<="").*?(?="")").Value;
                    gameData[label] = value;
                }
                else if (PGNFileLine != "") //Move line
                {
                    gameMoveList +=  PGNFileLine;
                }
            }
            return fullPgnData;
        }

        /// <summary>
        /// Updates 'data' with unique information from gameData
        /// Uses unique identifiers from game, event, and player to overwrite duplicates
        /// </summary>
        /// <param name="data"></param>
        /// <param name="gameData"></param>
        /// <param name="moveList"></param>
        void RecordGameData(ChessData data, Dictionary<string, string> gameData, string moveList)
        {
            Game pgnGame = new Game()
            {
                round = gameData["Round"],
                result = gameData["Result"],
                moves = moveList,
                whitePlayerName = gameData["White"],
                blackPlayerName = gameData["Black"],
                eventName =  gameData["Event"], //duplicate data kept for key lookup
                eventSite =  gameData["Site"],
                eventDate =  gameData["Date"]
            };
            ChessEvent pgnEvent = new ChessEvent()
            {
                name = gameData["Event"],
                site = gameData["Site"],
                date = gameData["Date"]
            };
            Player pgnWhitePlayer = new Player()
            {
                name = gameData["White"],
                elo = gameData["WhiteElo"]
            };
            Player pgnBlackPlayer = new Player()
            {
                name = gameData["Black"],
                elo = gameData["BlackElo"]
            };

            //Serial IDs are not added before communication with the database, so other unique identifiers are used
            //to prevent duplicate data entries in pgnData
            //  Players uniquely identified by name in data
            //  Events uniquely identified by name, site, and event data
            //  Games uniquely identified by round, event identifiers, and player identifiers
            fullPgnData.players[pgnWhitePlayer.name] = pgnWhitePlayer;
            fullPgnData.players[pgnBlackPlayer.name] = pgnBlackPlayer;
            fullPgnData.events[GetEventKey(pgnEvent.name, pgnEvent.site, pgnEvent.date)] = pgnEvent;
            fullPgnData.games[
                    pgnGame.round + pgnEvent.name + pgnEvent.site + pgnEvent.date + pgnWhitePlayer.name +
                    pgnBlackPlayer.name] =
                pgnGame;
        }

        /// <summary>
        /// Returns key for ChessData.events (for consistency)
        /// </summary>
        /// <param name="eventName"></param>
        /// <param name="eventSite"></param>
        /// <param name="eventDate"></param>
        /// <returns></returns>
        string GetEventKey(string eventName, string eventSite, string eventDate)
        {
            return eventName + eventSite + eventDate;
        }
        

        /// <summary>
        /// Queries the database for games that match all the given filters.
        /// The filters are taken from the various controls in the GUI.
        /// </summary>
        /// <param name="white">The white player, or "" if none</param>
        /// <param name="black">The black player, or "" if none</param>
        /// <param name="opening">The first move, e.g. "1.e4", or "" if none</param>
        /// <param name="winner">The winner as "W", "B", "D", or "" if none</param>
        /// <param name="useDate">true if the filter includes a date range, false otherwise</param>
        /// <param name="start">The start of the date range</param>
        /// <param name="end">The end of the date range</param>
        /// <param name="showMoves">true if the returned data should include the PGN moves</param>
        /// <returns>A string separated by newlines containing the filtered games</returns>
        private async Task<string> PerformQuery(string white, string black, string opening,
            string winner, bool useDate, DateTime start, DateTime end, bool showMoves)
        {
            // This will build a connection string to your user's database on atr,
            // assuimg you've typed a user and password in the GUI
            string connection = GetConnectionString();

            // Build up this string containing the results from your query
            string parsedResult = "";

            // Use this to count the number of rows returned by your query
            // (see below return statement)
            int numRows = 0;

            await using var conn = NpgsqlDataSource.Create(connection);

            try
            {
                
                await using var selectCommand = conn.CreateCommand(
                    "SELECT e.name, e.site, e.date, wp.name, wp.elo, bp.name, bp.elo, g.result, g.moves " +
                    "FROM games g " + 
                    "JOIN events e ON g.eid = e.eid " + 
                    "JOIN players wp ON g.whiteplayer = wp.pid " + 
                    (white != "" ? "AND wp.name = " + white + " ": "") + 
                    "JOIN players bp ON g.blackplayer = bp.pid " +
                    "LIMIT 10;");

                var reader = await selectCommand.ExecuteReaderAsync();
                
                while (await reader.ReadAsync())
                {
                    //For each player
                    numRows++;
                    parsedResult += 
                        "\nEvent: " + reader.GetString(0) +
                        "\nSite: " +  reader.GetString(1) +
                        "\nDate: " + reader.GetDateTime(2) + 
                        "\nWhite: " + reader.GetString(3) + " (" + reader.GetInt32(4) + ")" +
                        "\nBlack: " + reader.GetString(5) + " (" + reader.GetInt32(6) + ")" + 
                        "\nResult " + reader.GetChar(7);
                    if (showMoves)
                        parsedResult += reader.GetString(8);
                    parsedResult += "\n";
                }


                // TODO:
                //   Generate and execute an SQL command,
                //   then parse the results into an appropriate string and return it.
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine(e.Message);
            }


            return numRows + " results\n" + parsedResult;
        }


        private string GetConnectionString()
        {
            //If you install postgres with homebrew, you can use this
            //connection string (with modifications) to connect to it instead of ATR
            //return "Server=localhost; Username=ben; database=chess";
            return "server=atr.eng.utah.edu;database=" + Database + ";Username=" + Username;
        }


        /// <summary>
        /// This method will run when the file chooser is used.
        /// It loads the files contents as an array of strings,
        /// then invokes the InsertGameData method.
        /// </summary>
        /// <param name="args">The event arguments, which contains the selected file name</param>
        private async void HandleFileChooser(EventArgs args)
        {
            try
            {
                string fileContent = string.Empty;

                InputFileChangeEventArgs eventArgs = args as InputFileChangeEventArgs ?? throw new Exception("unable to get file name");
                if (eventArgs.FileCount == 1)
                {
                    var file = eventArgs.File;
                    if (file is null)
                    {
                        return;
                    }

                    // load the chosen file and split it into an array of strings, one per line
                    using var stream = file.OpenReadStream(1000000); // max 1MB
                    Console.WriteLine("Starting to read file");
                    using var reader = new StreamReader(stream);                   
                    fileContent = await reader.ReadToEndAsync();
                    string[] fileLines = fileContent.Split(new string[] { "\r\n", "\r", "\n" }, StringSplitOptions.None);

                    // insert the games, and don't wait for it to finish
                    // _ = throws away the task result, since we aren't waiting for it
                    Console.WriteLine("Read file, about to process it");
                    _ = InsertGameData(fileLines);
                }
            }
            catch (Exception e)
            {
                Debug.WriteLine("an error occurred while loading the file..." + e);
            }
        }

    }

}