package assignment08;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.awt.geom.Point2D;
import java.util.ArrayList;
import java.util.Arrays;

import static org.junit.jupiter.api.Assertions.*;

class GraphTest {

    Graph basicGraph;
    Graph graphWithBasicSearch;

    @BeforeEach
    void setup()
    {
        Node b1 = new Node(0, 0);
        Node b2 = new Node(1, 0);
        Node b3 = new Node(2, 0);
        b1.addNeighbor(b2);
        b2.addNeighbor(b1);
        b2.addNeighbor(b3);
        b3.addNeighbor(b2);
        basicGraph = new Graph(new ArrayList<>(Arrays.asList(b1,b2,b3)));

        Node n1 = new Node(0, 0);
        Node n2 = new Node(1, 0);
        Node n3 = new Node(2, 0);
        Node n4 = new Node(3, 0);
        Node nShort = new Node(0, 1);
        Node nOrphan = new Node(2, 2);
        n1.addNeighbor(n2);
        n1.addNeighbor(nShort);
        n2.addNeighbor(n3);
        n2.addNeighbor(n1);
        n3.addNeighbor(n4);
        n3.addNeighbor(n1);
        n4.addNeighbor(n3);
        n4.addNeighbor(nShort);
        nShort.addNeighbor(n4);
        nShort.addNeighbor(n1);
        graphWithBasicSearch = new Graph(new ArrayList<>(Arrays.asList(n1,n2,n3,n4,nShort, nOrphan)));
    }


    @Test
    void pathFinderLookup() {
        assertNotNull(basicGraph.lookUpNode(new Point2D.Double(2,0)));
        assertNull(basicGraph.lookUpNode(new Point2D.Double(3,0)));
    }

    @Test
    void pathFinderBasicSearch(){
        ArrayList<Node> pathToEnd = basicGraph.pathFinderSearch(new Point2D.Double(0,0), new Point2D.Double(2,0));
        assertEquals(pathToEnd.size(), 3);
        assertEquals(pathToEnd.get(0).positionXY, new Point2D.Double(2,0) );
        assertEquals(pathToEnd.get(2).positionXY, new Point2D.Double(0,0) );
    }

    @Test
    void pathFinderShortSearch(){
        ArrayList<Node> shortestPathToEnd = graphWithBasicSearch.pathFinderSearch(new Point2D.Double(0,0), new Point2D.Double(3,0));
        assertEquals(3, shortestPathToEnd.size());
        assertEquals(new Point2D.Double(3,0), shortestPathToEnd.get(0).positionXY);
        assertEquals(new Point2D.Double(0,1), shortestPathToEnd.get(1).positionXY);
        assertEquals(new Point2D.Double(0,0), shortestPathToEnd.get(2).positionXY);
    }

    @Test
    void pathFinderCantFind(){
        assertNull(graphWithBasicSearch.pathFinderSearch(new Point2D.Double(0,0), new Point2D.Double(2,2)));
    }
}