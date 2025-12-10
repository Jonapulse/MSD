package assignment08;

import java.awt.geom.Point2D;
import java.util.ArrayList;

public class PathFinder {
    public static void solveMaze(String inputFile, String outputFile){
        char[][] maze = getMazeFromFile(inputFile);
        ArrayList<Node> solvedPath = getMazeGraph(maze).pathFinderSearch(getPointWithValue(maze, 'S'), getPointWithValue(maze, 'G'));
        updateMazeWithSolution(maze, solvedPath);
        writeSolutionToFile(maze, outputFile);
    }

    /**
     * Converts an input file to an int[][] describe a maze with these characteristics:
     * * 1st line of input file is "<height> <width>" as in "5 5" for a 5x5 maze
     * * For subsequent lines...
     * * 'X' is a wall pacman cannot travel through
     * * ' ' is a travelable space
     * * 'S' is the starting point
     * * 'G' is the end point
     * @param inputFile
     * @return
     */
    static char[][] getMazeFromFile(String inputFile) {
        return null;
    }

    /**
     *
     * @param maze
     * @return
     */
    static Graph getMazeGraph(char[][] maze) {
        Node[][] mazeNodesInGrid = new Node[maze.length][maze[0].length];
        ArrayList<Node> mazeNodes = new ArrayList<>();

        //Initialize all valid spaces as nodes
         //
        for (int i = 0; i < maze.length; i++){
            mazeNodesInGrid[i] = new Node[maze[0].length];
            for (int j = 0; j < maze[0].length; j++){
                if(maze[i][j] == 'S' || maze[i][j] == 'G' || maze[i][j] == ' '){
                    Node newNode = new Node(i, j);
                    mazeNodesInGrid[i][j] = newNode;
                    mazeNodes.add(newNode);
                }
            }
        }

        //For all nodes, check all neighbors
         //
        for (int i = 0; i < mazeNodesInGrid.length; i++){
            for (int j = 0; j < mazeNodesInGrid[0].length; j++){
                if(mazeNodesInGrid[i][j] != null)
                {
                    if(i - 1 >= 0 && mazeNodesInGrid[i - 1][j] != null)
                        mazeNodesInGrid[i][j].addNeighbor(mazeNodesInGrid[i - 1][j]);
                    if(i + 1 < mazeNodesInGrid.length && mazeNodesInGrid[i + 1][j] != null)
                        mazeNodesInGrid[i][j].addNeighbor(mazeNodesInGrid[i + 1][j]);
                    if(j - 1 >= 0 && mazeNodesInGrid[i][j - 1] != null)
                        mazeNodesInGrid[i][j].addNeighbor(mazeNodesInGrid[i][j - 1]);
                    if(j + 1 < mazeNodesInGrid[0].length && mazeNodesInGrid[i][j + 1] != null)
                        mazeNodesInGrid[i][j].addNeighbor(mazeNodesInGrid[i][j + 1]);
                }
            }
        }

        return new Graph(mazeNodes);
    }

    /**
     * Utitily class for finding start and end
     * @param maze
     * @param target
     * @return Point2D(x, y)
     */
    static Point2D getPointWithValue(char[][] maze, char target)
    {
        for(int i = 0; i < maze.length; i++){
            for(int j = 0; j < maze[0].length; j++){
                if (maze[i][j] == target){
                    return new Point2D.Double(i, j);
                }
            }
        }
        return null;
    }


    private static ArrayList<Node> breadthFirstSearch(Graph mazeGraph, Point2D s, Point2D g) {

    }



    private static void updateMazeWithSolution(char[][] maze, ArrayList<Node> solvedPath) {
        for(Node node : solvedPath){
            Point2D pathStep = node.positionXY;
            maze[(int)pathStep.getX()][(int)pathStep.getY()] = '*';
        }
    }

    private static void writeSolutionToFile(char[][] chars, String outputFile) {

    }





}
