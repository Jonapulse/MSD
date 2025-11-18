import assignment03.SortedSet;
import assignment03.BinarySearchSet;

import java.util.Random;

public class SortedSetTimer extends TimerTemplate {

    SortedSet<Integer> testSet;
    Random rand = new Random();

    public SortedSetTimer(int[] problemSizes, int timesToLoop) {
        super(problemSizes, timesToLoop);
    }

    @Override
    protected void setup(int n) {
        testSet = new BinarySearchSet<>();
        for(int i = 0; i < n; i++)
            testSet.add(i);
    }

    @Override
    protected void timingIteration(int n) {
        //testSet.contains(n);
        int check = rand.nextInt(n);
        testSet.add(check);
    }

    @Override
    protected void compensationIteration(int n) {
        int get = rand.nextInt(n);
    }
}
