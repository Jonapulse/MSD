/**
 * Workspace for SortUtil timing analysis
 */
public class HashTableAnalysis {
    public static void main(String[] args) {
        //Mergesort Threshold - best?
        //Threshold: 100, 500, 1000, 5000, 10000
        //using worst case n
         //

        /*
        int[] problemSizes = {(int)Math.pow(2, 10), (int)Math.pow(2, 10), (int)Math.pow(2, 10), (int)Math.pow(2, 10), //Start buffer
                (int)Math.pow(2, 10), (int)Math.pow(2,11), (int)Math.pow(2,12), (int)Math.pow(2,13),
                (int)Math.pow(2,14),(int)Math.pow(2,15), (int)Math.pow(2,16), (int)Math.pow(2,17), (int)Math.pow(2,18),
                (int)Math.pow(2,19), (int)Math.pow(2,20),
                (int)Math.pow(2, 10),(int)Math.pow(2, 10),}; //End buffer
         */
       /* int[] problemSizes = {(int)Math.pow(2,11), (int)Math.pow(2,11), (int)Math.pow(2,11), (int)Math.pow(2,11),
                (int)Math.pow(2,11), (int)Math.pow(2,11), (int)Math.pow(2,11), (int)Math.pow(2,11), (int)Math.pow(2,11),
                (int)Math.pow(2,16), (int)Math.pow(2,16), (int)Math.pow(2,16), (int)Math.pow(2,16),};*/
        int[] problemSizes = {1};
        HashTimingTest t = new HashTimingTest(problemSizes, 100);
        var results = t.run();

        System.out.println("n, time");
        for(var result: results){
            System.out.println(result.n() + ", " + (result.avgNanoSecs()) / 1_000_000 + "ms");
        }
    }
}
