package assignment08;

import java.awt.geom.Point2D;
import java.util.ArrayList;

public class Node {
    //Note: positionXY used for IDing nodes, but the solution is a graph search with no knowledge of 'X' and 'Y'
    public Point2D positionXY;
    public ArrayList<Node> neighbors;

    public Node(int x, int y) {
        positionXY = new Point2D.Double(x,y);
        this.neighbors = new ArrayList<Node>();
    }

    public void addNeighbor(Node n){
        neighbors.add(n);
    }

}
