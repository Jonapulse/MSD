package assignment09;

import org.w3c.dom.Node;

import java.util.ArrayList;
import java.util.Random;

public class BSPTree {

    private Node root = null;
    private Random r = new Random();

    class Node{
        Segment seg;
        Node left, right;

        public Node(Segment seg){
            this.seg = seg;
            left = right = null;
        }
    }

    public BSPTree() {}

    public BSPTree(ArrayList<Segment> segs) {
        root = bulkConstructBSPTree(segs);
    }

    Node bulkConstructBSPTree(ArrayList<Segment> segs){
        Node subRoot = new Node(segs.get(r.nextInt(segs.size())));
        ArrayList<Segment> leftSegs = new ArrayList<>();
        ArrayList<Segment> rightSegs = new ArrayList<>();

        for(Segment seg : segs){
            double side = subRoot.seg.whichSide(seg);
            if(side == -1)
                leftSegs.add(seg);
            else if (side == 1)
                rightSegs.add(seg);
            else{
                Segment[] leftRight = subRoot.seg.split(seg);
                leftSegs.add(leftRight[0]);
                rightSegs.add(leftRight[1]);
            }
        }
        subRoot.left = bulkConstructBSPTree(leftSegs);
        subRoot.right = bulkConstructBSPTree(rightSegs);
        return subRoot;
    }

    /**
     * Inserts segment into BSPTree, splitting if necessary
     * @param seg
     */
    void insert(Segment seg) {
        insertRec(root, seg);
    }

    Node insertRec(Node n, Segment seg) {
        if(n == null)
            return new Node(seg);

        double side = n.seg.whichSide(seg);
        if(side == -1)
            n.left = insertRec(n.left, seg);
        else if(side == 1)
            n.right = insertRec(n.right, seg);
        else{
            Segment[] leftRight = n.seg.split(seg);
            n.left = insertRec(n.left, leftRight[0]);
            n.right = insertRec(n.right, leftRight[1]);
        }

        return n;
    }

    void traverseFarToNear(double x, double y, SegmentCallback callback) {
        traverseFarToNearRecurse(root, x, y, callback);
    }

    void traverseFarToNearRecurse(Node n, double x, double y, SegmentCallback callback) {
         int leftProximity = n.left.seg.whichSidePoint(x, y);
         traverseFarToNearRecurse(leftProximity < 0 ? n.left : n.right, x, y, callback);
         callback.callback(n.seg);
         traverseFarToNearRecurse(leftProximity < 0 ? n.right : n.left, x, y, callback);
    }

    Segment collision(Segment query){
        return collisionRec(root, query);
    }

    Segment collisionRec(Node n, Segment query){
        if(n.seg.intersects(query))
            return n.seg;
        double side = n.seg.whichSide(query);
        if(side == -1)
            return collisionRec(n.left, query);
        else if(side == 1)
            return collisionRec(n.right, query);
        else{
            Segment foundCollision = collisionRec(n.left, query);
            if(foundCollision != null)
                return foundCollision;
            else
                return collisionRec(n.right, query);
        }
    }
}
