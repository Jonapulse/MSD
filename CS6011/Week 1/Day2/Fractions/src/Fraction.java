public class Fraction {

    static long n, d;

    public Fraction()
    {
        n = 0;
        d = 1;
    }

    public Fraction(long n, long d){
        this.n = n;
        this.d = d;
        if(this.d == 0)
            throw new ArithmeticException();

    }

    void testFractions()
    {
        try{
            Fraction f = new Fraction(10, 0);
        } catch(ArithmeticException e) {
            System.out.println("Properly throwing divide-by-zero exception");
        }
    }

    void main() {
        testFractions();
    }
}
