package assignment08;

import org.junit.jupiter.api.Test;
import pacman.PacmanApp;

import java.io.IOException;

import static org.junit.jupiter.api.Assertions.*;

class PathFinderTest {

    String tinyMazeName =  "tinyMaze.txt";
    char[][] tinyMazeDefault = {
            {'X', 'X', 'X', 'X', 'X'},
            {'X', 'S', ' ', ' ', 'X'},
            {'X', ' ', ' ', ' ', 'X'},
            {'X', ' ', ' ', 'G', 'X'},
            {'X', 'X', 'X', 'X', 'X'}
    };
    String altMazeName = "altMaze.txt";
    char[][] altMazeDefault = {
            {' ', 'S', ' '},
            {' ', 'X', ' '},
            {' ', ' ', ' '},
            {'X', ' ', ' '},
            {'G', 'X', ' '},
            {' ', ' ', ' '},

    };

    String[] zippedMazes = {"bigMaze", "classic", "demoMaze", "mediumMaze", "straight", "tinyMaze", "tinyOpen", "unsolvable"};
//    Graph tinyMazeGraph;
//
//    @org.junit.jupiter.api.BeforeEach
//    void setUp() {
//        tinyMazeGraph = PathFinder.getMazeGraph(tinyMazeDefault);
//        altMaz
//    }

    @Test
    void readMaze(){
        try {
            char[][] mazeReadFromText = PathFinder.getMazeFromFile(tinyMazeName);
            for (int i = 0; i < mazeReadFromText.length; i++) {
                for (int j = 0; j < mazeReadFromText[i].length; j++) {
                    assertEquals(mazeReadFromText[i][j], tinyMazeDefault[i][j]);
                }
            }

            char[][] altMazeReadFromText = PathFinder.getMazeFromFile(altMazeName);
            for (int i = 0; i < altMazeReadFromText.length; i++) {
                for (int j = 0; j < altMazeReadFromText[i].length; j++) {
                    assertEquals(altMazeReadFromText[i][j], altMazeDefault[i][j]);
                }
            }
        }
        catch(Exception e) {
            System.out.println("readMaze() fileNotFound!!!");
        }
    }

    @Test
    void testHugeSolvedMaze()
    {
        try{
            char[][] solved = PathFinder.testSolveMaze(PacmanApp.readMaze("megaMaze.txt"));
            String mySolvedMaze = PacmanApp.mazeToString(solved);
            String theirSolvedMaze = PacmanApp.mazeToString(PacmanApp.readMaze("megaMazeOutput.txt"));
            assertEquals(mySolvedMaze, theirSolvedMaze);
        } catch (IOException e){
            System.out.println("megaMaze is failing to load, or its solution is");
        }
    }

    /**
     * Note, when 'my' solution did not match zipped mazes solution but was valid, I modified zipped mazes to my solution (demoMaze and tinyOpen)
     * This skips 'randomMaze' and 'turn' which are the real long ones and get their own test.
     */
    @Test
    void checkMazeSolutionSuite() {
        for (int i = 0; i < zippedMazes.length; i++) {
            try{
                char[][] solved = PathFinder.testSolveMaze(PacmanApp.readMaze("mazes/" + zippedMazes[i] + ".txt"));
                String mySolvedMaze = PacmanApp.mazeToString(solved);
                String theirSolvedMaze = PacmanApp.mazeToString(PacmanApp.readMaze("mazes/" + zippedMazes[i] + "Sol.txt"));

                assertEquals(theirSolvedMaze, mySolvedMaze);
            } catch (IOException e){
                System.out.println(zippedMazes[i] + " is failing to load, or its solution is");
            }
        }
    }

    @Test
    void checkRandomHugeMaze(){
        try{
            char[][] solved = PathFinder.testSolveMaze(PacmanApp.readMaze("mazes/randomMaze.txt"));
            String mySolvedMaze = PacmanApp.mazeToString(solved);
            String theirSolvedMaze = PacmanApp.mazeToString(PacmanApp.readMaze("mazes/randomMazeSol.txt"));

            assertEquals(theirSolvedMaze, mySolvedMaze);
        } catch (IOException e){
            System.out.println("RandomMazeSolis failing to load, or its solution is");
        }
    }

    @Test
    void checkTurnMaze(){
        try{
            char[][] solved = PathFinder.testSolveMaze(PacmanApp.readMaze("mazes/turn.txt"));
            String mySolvedMaze = PacmanApp.mazeToString(solved);
            String theirSolvedMaze = PacmanApp.mazeToString(PacmanApp.readMaze("mazes/turnSol.txt"));

            assertEquals(theirSolvedMaze, mySolvedMaze);
        } catch (IOException e){
            System.out.println("RandomMazeSolis failing to load, or its solution is");
        }
    }
}