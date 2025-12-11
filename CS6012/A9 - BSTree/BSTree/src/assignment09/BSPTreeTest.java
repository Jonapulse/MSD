package assignment09;

import org.junit.jupiter.api.Test;

import java.util.ArrayList;

import static org.junit.jupiter.api.Assertions.*;

class BSPTreeTest {

    @org.junit.jupiter.api.Test
    void insert() {
    }

    @org.junit.jupiter.api.Test
    void traverseFarToNear() {
    }

    @org.junit.jupiter.api.Test
    void collision() {
    }

    @Test
    void bulkConstructBSPTree() {
        ArrayList<Segment> smallList = new ArrayList<>();
        for (int i = 0; i < 5; i++) {
            smallList.add(new Segment(Math.random(), Math.random(), Math.random(), Math.random()));
        }
        BSPTree bspTree = new BSPTree(smallList);
    }
}