
import assignment09.BSPTree;
import assignment09.Segment;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class BSPTreeTimingTest extends TimerTemplate {

    ArrayList<Segment> segments;
    BSPTree bspTree;

    ArrayList<String> words;
    public BSPTreeTimingTest(int[] problemSizes, int timesToLoop) {
        super(problemSizes, timesToLoop);
    }

    @Override
    protected void setup(int n) {
        segments = new ArrayList<Segment>();
        for(int i = 0; i < n; i++){
            segments.add(new Segment(0 + i,0 + i, 0 + i, 1 + i));
        }
        bspTree = new BSPTree(segments);
    }

    @Override
    protected void timingIteration(int n) {
       // bspTree.collision(new Segment(0, 0, 1, 1));
        bspTree.analysis_collision(new Segment(0, 0, 1, 1));
    }

    @Override
    protected void compensationIteration(int n) {
        BSPTree bspTree = new BSPTree();
    }


}
