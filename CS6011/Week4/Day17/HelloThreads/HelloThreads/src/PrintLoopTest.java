public class PrintLoopTest implements Runnable {
    @Override
    public void run() {
        for(int i = 1; i <= 100; i++){
            System.out.print("hello number " + i + " from thread number " + Thread.currentThread().threadId() + "; ");
            if(i % 10 == 0)
                System.out.print('\n');
        }
    }
}
