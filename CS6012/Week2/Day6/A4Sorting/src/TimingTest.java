import assignment04.SortUtil;

import java.util.ArrayList;
import java.util.Comparator;

public class TimingTest extends TimerTemplate {

    ArrayList<Integer> averageCase;

    public TimingTest(int[] problemSizes, int timesToLoop) {
        super(problemSizes, timesToLoop);
    }

    @Override
    protected void setup(int n) {
        averageCase = SortUtil.generateAverageCase(n);
    }

    @Override
    protected void timingIteration(int n) {
        SortUtil.mergesort(averageCase, Comparator.naturalOrder());
    }

    @Override
    protected void compensationIteration(int n) {
        //null
    }
}
