import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Assertions;


class FractionTest {

    @Test
    void testConstructor(){
        Fraction f = new Fraction();
        Assertions.assertEquals("0",f.toString());

        Fraction fBasic =  new Fraction(1, 2);
        Assertions.assertEquals("1/2", fBasic.toString());
    }

    @Test
    void testNegative1()
    {
        Fraction f1 = new Fraction(-1, 2);
        Assertions.assertEquals("-1/2", f1.toString());
    }

    @Test
    void TestNegative2()
    {
        Fraction f2 = new Fraction(1, -2);
        Assertions.assertEquals("-1/2", f2.toString());
    }

    @Test
    void TestNegative3()
    {
        Fraction f3 = new Fraction(-1, -2);
        Assertions.assertEquals("1/2", f3.toString());
    }

    @Test
    void TestNegative4()
    {
        Fraction f4 = new Fraction(4, -16);
        Assertions.assertEquals("-1/4", f4.toString());
    }

    @Test
    void testReduced1()
    {
        Fraction f1 = new Fraction(2, 4);
        Assertions.assertEquals("1/2", f1.toString());
    }

    @Test
    void testReduced2()
    {
        Fraction f2 = new Fraction(-2, 4);
        Assertions.assertEquals("-1/2", f2.toString());
    }

    @Test
    void TestPlus1()
    {
        Fraction f1 = new Fraction(4, 6);
        Fraction f2 = new Fraction(3, 4);
        Assertions.assertEquals("17/12", f1.plus(f2).toString());
    }

    @Test
    void TestPlus2()
    {
        Fraction f1 = new Fraction(3, 2);
        Fraction f2 = new Fraction(-4, 3);
        Assertions.assertEquals("1/6", f1.plus(f2).toString());
    }

    @Test
    void TestPlus3()
    {
        Fraction f1 = new Fraction(3, 2);
        Fraction f2 = new Fraction(0, 3);
        Assertions.assertEquals("3/2", f1.plus(f2).toString());
    }

    @Test
    void TestPlus4()
    {
        Fraction f1 = new Fraction(3, 2);
        Fraction f2 = new Fraction(-6, 4);
        Assertions.assertEquals("0", f1.plus(f2).toString());
    }

    @Test
    void TestMinus1()
    {
        Fraction f1 = new Fraction(2, 3);
        Fraction f2 = new Fraction(3, 4);
        Assertions.assertEquals("-1/12", f1.minus(f2).toString());
    }

    @Test
    void TestMinus2()
    {
        Fraction f1 = new Fraction(3, 2);
        Fraction f2 = new Fraction(-4, 3);
        Assertions.assertEquals("17/6", f1.minus(f2).toString());
    }

    @Test
    void TestMinus3()
    {
        Fraction f1 = new Fraction(3, 2);
        Fraction f2 = new Fraction(0, 3);
        Assertions.assertEquals("3/2", f1.minus(f2).toString());
    }

    @Test
    void TestMinus4()
    {
        Fraction f1 = new Fraction(3, 2);
        Fraction f2 = new Fraction(6, 4);
        Assertions.assertEquals("0", f1.minus(f2).toString());
    }

    @Test
    void testTimes1()
    {
        Fraction f1 = new Fraction(4, 6);
        Fraction f2 = new Fraction(3, 4);
        Assertions.assertEquals("1/2", f1.times(f2).toString());
    }

    @Test
    void testTimes2()
    {
        Fraction f1 = new Fraction(3, 2);
        Fraction f2 = new Fraction(0, 4);
        Assertions.assertEquals("0", f1.times(f2).toString());
    }

    @Test
    void testTimes3()
    {
        Fraction f1 = new Fraction(4, 6);
        Fraction f2 = new Fraction(-3, 4);
        Assertions.assertEquals("-1/2", f1.times(f2).toString());
    }

    @Test
    void testDivide1()
    {
        Fraction f1 = new Fraction(4, 6);
        Fraction f2 = new Fraction(3, 4);
        Assertions.assertEquals("8/9", f1.dividedBy(f2).toString());
    }

    @Test
    void testDivide2()
    {
        Fraction f1 = new Fraction(4, 6);
        Fraction f2 = new Fraction(-3, 4);
        Assertions.assertEquals("-8/9", f1.dividedBy(f2).toString());
    }

    @Test
    void testDivide3()
    {
        Fraction f1 = new Fraction(5, 6);
        Fraction f2 = new Fraction(-1, 4);
        Assertions.assertEquals("-10/3", f1.dividedBy(f2).toString());
    }

    @Test
    void TestToDouble1()
    {
        Fraction f1 = new Fraction(1, 2);
        Assertions.assertEquals(0.5, f1.toDouble(), 0.01);
    }

    @Test
    void TestToDouble2()
    {
        Fraction f1 = new Fraction(1, 3);
        Assertions.assertEquals(1.0/3.0, f1.toDouble(), 0.01);
    }


    @Test
    void TestReciprocal1()
    {
        Fraction f1 = new Fraction(1, 3);
        Assertions.assertEquals("3", f1.reciprocal().toString());
    }

    @Test
    void TestReciprocal2()
    {
        Fraction f1 = new Fraction(-1, 2);
        Assertions.assertEquals("-2", f1.reciprocal().toString());
    }

    @Test
    void TestReciprocal3()
    {
        Fraction f1 = new Fraction(6, 2);
        Assertions.assertEquals("1/3", f1.reciprocal().toString());
    }

    @Test
    void testCompare()
    {
        Fraction f1 = new Fraction(1, 2);
        Fraction f2 = new Fraction(1, 3);
        Fraction f3 = new Fraction(1, 2);

        Assertions.assertEquals(-1, f1.compareTo(f2));
        Assertions.assertEquals(0, f1.compareTo(f3));
        Assertions.assertEquals(1, f2.compareTo(f1));
    }
}