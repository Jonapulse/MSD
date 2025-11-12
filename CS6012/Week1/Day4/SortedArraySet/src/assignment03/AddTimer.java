package assignment03;

import java.util.ArrayList;
import java.util.Random;

public class AddTimer extends TimerTemplate{

    BinarySearchSet<Integer> testSet = new BinarySearchSet<>();
    Integer findMe;

    public AddTimer(int[] problemSizes, int timesToLoop)
    {
        super(problemSizes, timesToLoop);
    }

    @Override
    protected void setup(int n) {
       BinarySearchSet<Integer> testSet = new BinarySearchSet<>();
       Random rand = new Random();
       Integer randomValue = -1;
       for(int i = 0; i < n; i++)
       {
           randomValue = Integer.valueOf(rand.nextInt(n));
           testSet.add(randomValue);
       }
       this.findMe = randomValue;
    }

    @Override
    protected void timingIteration(int n) {
        boolean isItInThere = testSet.contains(findMe);
    }

    @Override
    protected void compensationIteration(int n) {
        //null
    }
}
