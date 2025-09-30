public class Fraction implements Comparable<Fraction> {

    private long n, d;

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

        reduce();
        normalize();

    }

    public Fraction plus(Fraction rhs)
    {
        long denominatorProduct = this.d * rhs.d;
        long new_n = this.n * rhs.d + rhs.n * this.d;
        long new_d = denominatorProduct;
        return new Fraction(new_n, new_d);
    }

    public Fraction minus(Fraction rhs)
    {
        long denominatorProduct = this.d * rhs.d;
        long new_n = this.n * rhs.d - rhs.n * this.d;
        long new_d = denominatorProduct;
        return new Fraction(new_n, new_d);
    }

    public Fraction times(Fraction rhs)
    {
        return new Fraction(this.n * rhs.n, this.d * rhs.d);
    }

    public Fraction dividedBy(Fraction rhs)
    {
        return this.times(rhs.reciprocal());
    }

    public Fraction reciprocal()
    {
        return new Fraction(this.d, this.n);
    }

    public String toString()
    {
        if(n == 0) //For zero
            return "0";
        else if( d == 1) //For whole numbers
            return "" + n;
        else
            return n + "/" + d;
    }

    public double toDouble()
    {
        return (double)n / d;
    }

    private long GCD()
    {
        long gcd = n;
        long remainder = d;
        while( remainder != 0 ) {
            long temp = remainder;
            remainder = gcd % remainder;
            gcd = temp;
        }
        return gcd;
    }

    private void reduce()
    {
        long gcd = GCD();
        n /= gcd;
        d /= gcd;
    }

    void normalize() {
        if (this.d < 0){
            this.d *= -1;
            this.n *= -1;
        }
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

    @Override
    public int compareTo(Fraction o) throws NullPointerException {
        if(o == null)
            throw new NullPointerException();
        double convFrac = o.toDouble();
        if(convFrac == this.toDouble()) return 0;
        else return convFrac < this.toDouble() ? -1 : 1;
    }
}
