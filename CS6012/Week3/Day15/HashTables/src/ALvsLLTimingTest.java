import assignment05.LinkedListStack;
import assignment05.ArrayStack;
import assignment05.Stack;

import java.util.ArrayList;
import java.util.Comparator;

public class ALvsLLTimingTest extends TimerTemplate {

    Stack testStack;

    public ALvsLLTimingTest(int[] problemSizes, int timesToLoop) {
        super(problemSizes, timesToLoop);
    }

    @Override
    protected void setup(int n) {
        testStack = new ArrayStack();
     //   testStack = new LinkedListStack();
        for(int i = 0; i < n; i++)
            testStack.push(i);
    }

    @Override
    protected void timingIteration(int n) {
        testStack.push(n);
      //  testStack.pop();
      //  testStack.peek();
    }

    @Override
    protected void compensationIteration(int n) {
        //null
    }
}
