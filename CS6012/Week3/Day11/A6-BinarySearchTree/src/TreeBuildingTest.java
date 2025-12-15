import assignment06.BinarySearchTree;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.Collections;
import java.util.TreeSet;

public class TreeBuildingTest extends TimerTemplate {

    private ArrayList<Integer> testArray;

    public TreeBuildingTest(int[] problemSizes, int timesToLoop) {
        super(problemSizes, timesToLoop);
    }

    @Override
    protected void setup(int n) {
        testArray = new ArrayList<>();
        //Sorted
        for(int i = 0; i < n; i++) {
            testArray.add(i);
        }

        //Shuffled, after sort creation
      //  Collections.shuffle(testArray);
    }

    @Override
    protected void timingIteration(int n) {
      //  BinarySearchTree<Integer> tree = new BinarySearchTree<>();
        TreeSet<Integer> tree = new TreeSet<>();
        for(int i = 0; i < testArray.size(); i++) {
            tree.add(i);
        }
    }

    @Override
    protected void compensationIteration(int n) {
     //   BinarySearchTree<Integer> tree = new BinarySearchTree<>();
        TreeSet<Integer> tree = new TreeSet<>();
        for(int i = 0; i < testArray.size(); i++) {
            //Nuffin'!
        }
    }
}
