public class Main{
    static int answer;

    public static void badSum(){
        answer = 0;
        int maxValue = 100;

        final int NUM_THREADS = 1;
        for(int i = 0; i < NUM_THREADS;  i++){
            Runnable r = new BadSumTest(i * maxValue / NUM_THREADS, Math.min((i + 1) * maxValue / NUM_THREADS, maxValue));
            Thread sumThread = new Thread(r);
            sumThread.start();
            try{
                sumThread.join();
            } catch(InterruptedException e)
            {
                System.out.println(sumThread.currentThread().threadId() + " failed to join");
            }
        }

        System.out.println("Computed answer: " + answer);
        System.out.println("Euler answer: " + (maxValue * (maxValue + 1) / 2));
    }

    public static void sayHello()
    {
        for(int i = 0; i < 10; i++){
            Thread th = new Thread(new PrintLoopTest());
            th.start();
            try{
                th.join();
            } catch (InterruptedException e){
                System.out.println(th.currentThread().threadId() + " failed to join");
            }
        }
    }
    public static void main(String[] args) {
        sayHello();

        //Lab Discussion:
        //Prior to adding join, the printing thread switches without a clear pattern
        //After adding join, the threads will consistently print from 1 to 100, from threadID 26 to 35

        badSum();

        //Running w/ join, badSum gives answer = 800,020,000 and Euler gives the same.
        //Without join, we get...
            //1: 0, consistently. - joined -> 800,020,000 (only correct one).
            //3: 477,958; 534,061; 3,748,842 - joined -> 800,059,999
            //10: 154,753,229; 137,809,173, 140,467,385 - joined -> 800,200,000
            //100: 769,302,171; 784,700,355; 779,325,247 - joined -> 802,000,000

        //Similar behavior for maxValue = 100. Euler: 5050
            //1: 0, consistently. - joined -> 5050
            //10: 4455 - joined -> 5500
            //100: 9604 - joined -> 10000

        //Why does this happen? Well... my best (wrong) guess is that some of the threads
        //are getting interrupted and dropped from the sum, but some of these answers are
        //coming in larger than the true answer, and interrupted threads can't account for.
        //So... ghosts. I think it's ghosts.
    }
}
