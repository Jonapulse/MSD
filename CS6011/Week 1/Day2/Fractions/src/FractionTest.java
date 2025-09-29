import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Assertions;


class FractionTest {

    @Test
    public void testConstructor(){
        Fraction f = new Fraction();
    }

    @Test
    public void testNegative1()
    {
        
    }

    @Test
    public void testTimes()
    {
        Fraction f1 = new Fraction(1, 2);
        Fraction f2 = new Fraction(1, 3);
        Fraction f3 = f1.times(f2);

        Assertions.assertEquals(f3.toString(), "1/6");
    }


}