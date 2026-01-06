package lab02;

import java.util.ArrayList;

public class Main {
    public static void main(String[] args){

        ArrayList<Integer> ns = new ArrayList<>();
        for(double n = 100; n < 1000000; n *= 1.5){
            ns.add((int)n);
        }

        //convert to int[]
        int[] problemSizes = new int[ns.size()];
        for(int i = 0; i < problemSizes.length; i++){
            problemSizes[i] = ns.get(i);
        }

        var timer = new RemoveFrontTimer(problemSizes, 10);
        var results = timer.run();
        System.out.println("n, time");
        for(var result: results){
            System.out.println(result.n() + ", " + result.avgNanoSecs());
        }
    }
}
