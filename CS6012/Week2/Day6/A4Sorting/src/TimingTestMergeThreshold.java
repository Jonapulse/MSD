import assignment04.SortUtil;

import java.util.ArrayList;
import java.util.Comparator;

public class TimingTestMergeThreshold extends TimerTemplate {

    ArrayList<Integer> averageCase;

    public TimingTestMergeThreshold(int[] problemSizes, int timesToLoop) {
        super(problemSizes, timesToLoop);
    }

    @Override
    protected void setup(int n) {
    }

    @Override
    protected void timingIteration(int n) {
        SortUtil.mergesort(new ArrayList<>(averageCase), Comparator.naturalOrder());
    }

    @Override
    protected void compensationIteration(int n) {
        ArrayList<Integer> dummy = new  ArrayList<>(averageCase);
    }
}
