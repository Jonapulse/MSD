
import assignment09.BSPTree;
import assignment09.Segment;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class BSPTreeTimingTest extends TimerTemplate {

    ArrayList<Segment> segments;

    ArrayList<String> words;
    public BSPTreeTimingTest(int[] problemSizes, int timesToLoop) {
        super(problemSizes, timesToLoop);
    }

    @Override
    protected void setup(int n) {
        segments = new ArrayList<Segment>();
        for(int i = 0; i < n; i++){
            segments.add(new Segment(i,i, i+0.5, i+0.5));
        }
    }

    @Override
    protected void timingIteration(int n) {
        BSPTree bspTree = new BSPTree(segments);
        /*
        for(int i = 0; i < segments.length(); i++)
            bspTree.add(segments.get(i)
         */
    }

    @Override
    protected void compensationIteration(int n) {
        BSPTree bspTree = new BSPTree();
    }


//    public static void main(String[] args) {
//        ArrayList<String> words = getWordsFromFile("linuxwords.txt");
//        System.out.println(words.size());
//    }
}
