package assignment08;

import java.awt.geom.Point2D;
import java.util.*;

/**
 * Graph class,
 * some expected methods exempted for a 'just-enough' solution to PathFinder
 * Graph nodes used a Point2D as an identifier
 */
public class Graph {
    ArrayList<Node> nodes = new ArrayList<Node>();

    public Graph(){
        nodes = new ArrayList<>();
    }
    public Graph(ArrayList<Node> nodes){
        this.nodes = nodes;
    }

    /**
     * A breadth-first search using Point2Ds as node IDs
     * This is a case-specific implementation
     * @param start
     * @param end
     * @return List of nodes from end to start of shortest path, or null if no valid path
     */
    public ArrayList<Node> pathFinderSearch(Point2D start, Point2D end){
        Node targetNode = lookUpNode(end);
        Set<Node> visited = new HashSet<Node>();
        Map<Node, Node> paths = new HashMap<Node, Node>();
        Queue<Node> q = new ArrayDeque<>();
        q.add(lookUpNode(start));
        while(!q.isEmpty()){
            Node n = q.poll();
            //Found target?
             //
            if(n.equals(targetNode)){
                ArrayList<Node> shortestPath = new ArrayList<>();
                shortestPath.add(n);
                while(paths.containsKey(n)){
                    n = paths.get(n);
                    shortestPath.add(n);
                }
                return shortestPath;
            }
            //Search Neighbors
             //
            for(Node neighbor: n.neighbors){
                if(!visited.contains(neighbor)){
                    visited.add(neighbor);
                    q.add(neighbor);
                    paths.put(neighbor, n);
                }
            }
        }

        //Not found!
        return null;
    }

    private Node lookUpNode(Point2D id){
        for(Node node : nodes){
            if(node.positionXY.equals(id)){
                return node;
            }
        }
        return null;
    }

}
