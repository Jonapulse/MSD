package msd.benjones;

import java.util.HashMap;

public class Main {

    public static void main(String[] args) throws InterruptedException {

   //     Network.makeSimpleNetwork(); //use this for testing/debugging
//        Network.makeProbablisticNetwork(5); //use this for the plotting part
//        Network.dump();
//
//        Network.startup();
//        Network.runBellmanFord();
//
//        System.out.println("done building tables!");
//        for(Router r : Network.getRouters()){
//            r.dumpDistanceTable();
//        }
//        System.out.println("total messages: " + Network.getMessageCount());

        HashMap<Integer, Float> sizeToAverageMessagesForConvergence = new HashMap<Integer,Float>();
        for(int n = 4; n <= (int)Math.pow(2, 10); n *= 2)
        {
            int messagesToConvergeSum = 0;
            int messagesToConvergeChecks = 5;
            for(int i = 0; i < messagesToConvergeChecks; i++)
            {
                Network.makeProbablisticNetwork(n);
                Network.startup();
                Network.runBellmanFord();
                messagesToConvergeSum += Network.getMessageCount();
            }
            sizeToAverageMessagesForConvergence.put(n, messagesToConvergeSum / (float)messagesToConvergeChecks);
        }
        for(Integer key : sizeToAverageMessagesForConvergence.keySet()) {
            System.out.println(key + " : " + sizeToAverageMessagesForConvergence.get(key));
        }

    }
}
