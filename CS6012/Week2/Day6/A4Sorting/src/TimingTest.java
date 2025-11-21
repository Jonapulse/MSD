import assignment04.SortUtil;

import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.Random;

public class TimingTest extends TimerTemplate {

    ArrayList<Integer> worstCase;

    public TimingTest(int[] problemSizes, int timesToLoop) {
        super(problemSizes, timesToLoop);
    }

    @Override
    protected void setup(int n) {

        worstCase = SortUtil.generateAverageCase(n);
    }

    @Override
    protected void timingIteration(int n) {
        SortUtil.mergesort(worstCase, Comparator.naturalOrder());
    }

    @Override
    protected void compensationIteration(int n) {
        //null
    }
}
