/**
 * Workspace for SortUtil timing analysis
 */
public class BSTTimingAnalysis
{
    public static void main(String[] args) {
        //Mergesort Threshold - best?
        //Threshold: 100, 500, 1000, 5000, 10000
        //using worst case n
         //


        int[] problemSizes = {(int)Math.pow(2,14),(int)Math.pow(2,15), (int)Math.pow(2,16), (int)Math.pow(2,17), (int)Math.pow(2,18),
                (int)Math.pow(2,19), (int)Math.pow(2,20)}; //End buffer

        /*int[] problemSizes = {(int)Math.pow(2,11), (int)Math.pow(2,11), (int)Math.pow(2,11), (int)Math.pow(2,11),
                (int)Math.pow(2,11), (int)Math.pow(2,11), (int)Math.pow(2,11), (int)Math.pow(2,11), (int)Math.pow(2,11),
                (int)Math.pow(2,16), (int)Math.pow(2,16), (int)Math.pow(2,16), (int)Math.pow(2,16),};*/
        TreeBuildingTest t = new TreeBuildingTest(problemSizes, 100);
        var results = t.run();

        System.out.println("n, time");
        for(var result: results){
            System.out.println(result.n() + ", " + (result.avgNanoSecs()));
        }
    }
}
