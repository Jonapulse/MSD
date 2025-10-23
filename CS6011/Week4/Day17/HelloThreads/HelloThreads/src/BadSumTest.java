public class BadSumTest implements Runnable{
    int minVal_;
    int maxVal_;

    @Override
    public void run() {
        for(int i = minVal_; i <= maxVal_; i++){
            Main.answer += i;
        }
    }

    public BadSumTest(int minVal, int maxVal) {
        minVal_ = minVal;
        maxVal_ = maxVal;
    }
}
