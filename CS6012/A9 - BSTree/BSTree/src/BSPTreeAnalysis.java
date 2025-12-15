/**
 * Workspace for SortUtil timing analysis
 */
public class BSPTreeAnalysis {
    public static void main(String[] args) {
        //Mergesort Threshold - best?
        //Threshold: 100, 500, 1000, 5000, 10000
        //using worst case n
         //


        int[] problemSizes = {(int)Math.pow(2,5)};

        BSPTreeTimingTest t = new BSPTreeTimingTest(problemSizes, 100);
        var results = t.run();

        System.out.println("n, time");
        for(var result: results){
            System.out.println(result.n() + ", " + (result.avgNanoSecs()) / 1_000_000 + "ms");
        }
    }
}
