import assignment04.SortUtil;

import java.util.ArrayList;
import java.util.Comparator;

public class TimingTestPivots extends TimerTemplate {

    ArrayList<Integer> averageCase;

    public TimingTestPivots(int[] problemSizes, int timesToLoop) {
        super(problemSizes, timesToLoop);
    }

    @Override
    protected void setup(int n) {
        averageCase = SortUtil.generateAverageCase(n);
    }

    @Override
    protected void timingIteration(int n) {
        SortUtil.quicksort(new ArrayList<>(averageCase), Comparator.naturalOrder());
    }

    @Override
    protected void compensationIteration(int n) {
        ArrayList<Integer> dummy = new  ArrayList<>(averageCase);
    }
}
