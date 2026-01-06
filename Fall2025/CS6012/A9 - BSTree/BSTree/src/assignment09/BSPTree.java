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

    /**
     * Builds a BSPTree using by selecting a random root and filling its left and right
     * sides Node's with recursively built sub-roots using the left and right sub-arrays.
     * @param segs
     * @return new subRoot
     */
    Node bulkConstructBSPTree(ArrayList<Segment> segs){
        if(segs == null || segs.isEmpty()) return null;

        int randomPick = r.nextInt(segs.size());
        Node subRoot = new Node(segs.get(randomPick));
        segs.remove(randomPick);

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
    public void insert(Segment seg) {
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

    /**
     * Traverses far to near recursively, applying the callback function
     * @param x
     * @param y
     * @param callback
     */
    void traverseFarToNear(double x, double y, SegmentCallback callback) {
        traverseFarToNearRecurse(root, x, y, callback);
    }

    /**
     * The recursive portion of traverseFarToNear
     * @param n
     * @param x
     * @param y
     * @param callback
     */
    void traverseFarToNearRecurse(Node n, double x, double y, SegmentCallback callback) {
        if (n == null)
            return;

        int side = n.seg.whichSidePoint(x, y);
        if(side < 0){
            traverseFarToNearRecurse(n.right, x, y, callback);
            callback.callback(n.seg);
            traverseFarToNearRecurse(n.left, x, y, callback);
        }else {
            traverseFarToNearRecurse(n.left, x, y, callback);
            callback.callback(n.seg);
            traverseFarToNearRecurse(n.right, x, y, callback);
        }

                /*
        Node farNode = null;
        Node nearNode = null;
        int leftProximity = n.left != null ? n.left.seg.whichSidePoint(x, y) : 0;
        int rightProximity = n.right != null ? n.right.seg.whichSidePoint(x, y) : 0;
        if (leftProximity < 0) {
            farNode = n.left;
            nearNode = n.right;
        } else if (leftProximity > 0) {
            farNode = n.right;
            nearNode = n.left;
        } else if (rightProximity < 0) {
            farNode = n.right; //and left node is null
        } else
            farNode = n.left;

        traverseFarToNearRecurse(farNode, x, y, callback);
        callback.callback(n.seg);
        traverseFarToNearRecurse(nearNode, x, y, callback);
        */
    }

    /**
     * Checks collision recursively
     * @param query
     * @return
     */
    public Segment collision(Segment query){
        return collisionRec(root, query);
    }

    public boolean collisionFound = false;

    public Segment analysis_collision(Segment query){
        this.traverseFarToNear(0, 0,
                (segment) -> {
                    if(segment.intersects(query)){
                        collisionFound = true;
                    }
                });
        return collisionFound ? query : null;
    }
    /**
     * The recursive portion of collision
     * @param n
     * @param query
     * @return seg that collides or null if no collision
     */
    Segment collisionRec(Node n, Segment query){
        if(n == null)
            return null;
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
