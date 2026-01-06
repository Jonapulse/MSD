package lab02;

import java.util.ArrayList;

public class RemoveFrontTimer extends TimerTemplate{
    ArrayList<Integer> arr;

    public RemoveFrontTimer(int[] problemSizes, int timesToLoop){
        super(problemSizes, timesToLoop);
    }

    @Override
    protected void setup(int n) {
        arr = new ArrayList<Integer>(n);
        for(int i=0;i<n;i++){
            arr.add(i);
        }
    }

    @Override
    protected void timingIteration(int n) {
        arr.remove(0);
        arr.add(-1);
    }

    @Override
    protected void compensationIteration(int n) {
        arr.set(arr.size() - 1, n);
    }
}
