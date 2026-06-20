using System.Diagnostics;
using Microsoft.AspNetCore.Components.Forms;
using Npgsql;
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
      string blackPlayerName, 
      string whitePlayerName, 
      int eid
      );

    private record struct ChessEvent(
      string name,
      string site,
      string date,
      string eid
      );

    private record struct Player(
      string name,
      string elo,
      string pid
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
      // This will build a connection string to your user's database on atr,
      // assuimg you've filled in the credentials in the GUI
      
      string connectionString = GetConnectionString();
      
      //wrap this in try/catch with exception printing so the UI doesn't swallow your exceptions
      try
      {
        ChessData data = ParseChessData(PGNFileLines);

        // TODO:
        //   Iterate through your data and generate appropriate insert commands
          
        // TODO:
        //   Update the Progress member variable every time progress has been made
        //   (e.g. one iteration of your upload loop)
        //   This will update the progress bar in the GUI
        //   Its value should be an integer representing a percentage of completion
        Progress = 0;

        // This tells the GUI to redraw after you update Progress (this should go inside your loop)
        await InvokeAsync(StateHasChanged);
          

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
        blackPlayerName = gameData["Black"]
      };
      ChessEvent pgnEvent = new ChessEvent()
      {
        name = gameData["Event"],
        site = gameData["Site"],
        date = gameData["Date"].Replace('.', '-'), //PostgreSQL's Date wants '-'
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
      fullPgnData.events[pgnEvent.name + pgnEvent.site + pgnEvent.date] = pgnEvent;
      fullPgnData.games[
          pgnGame.round + pgnEvent.name + pgnEvent.site + pgnEvent.date + pgnWhitePlayer.name +
          pgnBlackPlayer.name] =
        pgnGame;

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
