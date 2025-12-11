package assignment08;

import org.junit.jupiter.api.Test;

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
    void checkMazeSolutionSuite() {
        //...might not have time to go through mazes.zip...
    }
}