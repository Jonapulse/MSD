/*
 * Author: Daniel Kopta and <add your names here>
 * July 2017

 * Testing program for your Fraction class.
 * These tests are not very thorough, and you will need to add your own.
*/

// Include the student's Fraction class
#include "Fraction.h"

// Standard includes
#include <iostream>
#include <string>
// Also include math so we can use the pow and abs functions (see below)
#include <cmath>

using std::cout;
using std::cin;
using std::endl;
using std::string;

bool CompareDoubles( double d1, double d );


/* Helper function for writing tests that compare strings.
 * Compares expected to result, and prints an error if they don't match.
 */
void Test( const string & message, const string & expected, const string & result )
{
  cout << "Test: " << message << endl;
  if(expected != result) {
    cout << "\tFAILED, expected: \"" << expected << "\", got: \"" << result << "\"" << endl;
  }
  else {
    cout << "\tPASSED" << endl;
  }
}

/* Helper function for writing tests that compare doubles (overloaded version of the above)
 * Compares expected to result, and prints an error if they don't match.
 */
void Test( const string & message, double expected, double result )
{
  cout << "Test: " << message << endl;
  if( !CompareDoubles( expected, result ) ) {
    cout << "\tFAILED, expected: " << expected << ", got: " << result << endl;
  }
  else {
    cout << "\tPASSED" << endl;
  }
}

/* Helper function for writing tests receive bools
 */
void Test( const string & message, bool result)
{
  cout << "Test: " << message << endl;
  if(!result) {
    cout << "\tFAILED, expected: true, got false" << endl;
  }
  else {
    cout << "\tPASSED" << endl;
  }
}

/*
 * Helper function
 * Returns whether or not two doubles are "equivalent",
 * within a certain error bound.
 *
 * As we know, floating point numbers are incapable of
 * precisely representing certain values, so to compare
 * equality, we must tolerate some absolute difference.
 */
bool CompareDoubles( double d1, double d2 )
{
  return std::abs( d1 - d2 ) < 1e-6;
}

/*
 * Basic constructor and toString tests
 */
void TestConstructors()
{
  std::string result = "";
  Fraction f1;
  result = f1.toString();
  Test( "Default constructor", "0/1", result );
  
  Fraction f2(1, 2);
  result = f2.toString();
  Test( "Basic constructor", "1/2", result );

  //TODO: Add your own additional tests here

}


/*
 * Negative fraction tests
 */
void TestNegative()
{
  std::string result = "";
  Fraction f1(-1, 2);
  result = f1.toString();
  Test( "Negative numerator", "-1/2", result );

  Fraction f2(1, -2);
  result = f2.toString();
  Test( "Negative denominator", "-1/2", result );

  Fraction f3(-1, -2);
  result = f3.toString();
  Test( "Negative numerator and denominator", "1/2", result );

  Fraction f4(4, -16);
  result = f4.toString();
  Test( "Negative denominator and reduce", "-1/4", result );

}


/*
 * Reduced fraction tests
 */
void TestReduced()
{
    std::string result = "";
    Fraction f1(2, 4);
    result = f1.toString();
    Test( "Reduce fraction (2/4)", "1/2", result );
    
    f1 = Fraction(-2, 4);
    result = f1.toString();
    Test( "Reduce fraction (-2/4)", "-1/2", result );
}


/*
 * Reciprocal tests
 */
void TestReciprocal()
{
    std::string result = "";
    Fraction f1(1, 3);
    f1 = f1.reciprocal();
    result = f1.toString();
    Test( "Reciprocal of simple", "3/1", result );
    
    Fraction f2(-1, 2);
    f2 = f2.reciprocal();
    result = f2.toString();
    Test( "Reciprocal of negative", "-2/1", result );
    
    Fraction f3(6, 2);
    f3 = f3.reciprocal();
    result = f3.toString();
    Test( "Reciprocal of non-reduced", "1/3", result );
}

/*
 * Fraction addition tests
 */
void TestPlus()
{
    std::string result = "";
    Fraction f1(4, 6);
    Fraction f2(3, 4);
    
    // Should result in 17/12
    Fraction f3 = f1.plus(f2);
    result = f3.toString();
    Test( "Addition of non-reduced", "17/12", result );
    
    //Addition of positive, negative
    f1 = Fraction(3, 2); // 9/6
    f2 = Fraction(-4, 3); // -8/6
    result = (f1 + f2).toString();
    Test("Addition of positive/negative", "1/6", result);
    
    //Addition of zero
    f1 = Fraction(3, 2);
    f2 = Fraction(0, 3);
    result = (f1 + f2).toString();
    Test("Addition of zero", "3/2", result);
    
    //Addition results in zero
    f1 = Fraction(3, 2);
    f2 = Fraction(-6, 4);
    result = (f1 + f2).toString();
    Test("Addition results in zero", "0", result);    
}

void TestToDouble()
{
  Fraction f1(1, 2);
  double result = f1.toDouble();
  Test( "toDouble (1/2)", 0.5, result );

  Fraction f2(1, 3);
  result = f2.toDouble();
  Test( "toDouble (1/3)", 1.0/3.0, result );
}

/*
 * Approximates pi using a summation of fractions.
 */
double ComputePi()
{
    Fraction sum;
    
    // We will only compute the first 4 terms
    // Note that even with long (64-bit) numbers,
    // the intermediate numbers required for fraction addition
    // become too large to represent if we go above k=4.
    for( long k = 0; k < 4; k++ )
    {
        Fraction multiplier( 1, pow(16, k) );
        Fraction firstTerm(  4, 8*k + 1 );
        Fraction secondTerm( 2, 8*k + 4 );
        Fraction thirdTerm(  1, 8*k + 5 );
        Fraction fourthTerm( 1, 8*k + 6 );
        
        Fraction temp = firstTerm.minus( secondTerm );
        temp = temp.minus( thirdTerm );
        temp = temp.minus( fourthTerm );
        
        Fraction product = multiplier.times( temp );
        
        sum = sum.plus( product );
    }
    
    return sum.toDouble();
}

void TestMinus()
{
    std::string result = "";
    Fraction f1(4, 6);
    Fraction f2(3, 4);
    
    // Should result in -1/12
    Fraction f3 = f1.minus(f2);
    result = f3.toString();
    Test( "Subtraction of non-reduced", "-1/12", result );
    
    //Subtraction of positive, negative
    f1 = Fraction(3, 2); // 9/6
    f2 = Fraction(-4, 3); // -8/6
    result = (f1 - f2).toString();
    Test("Subtraction of positive/negative", "17/6", result);
    
    //Subtraction of zero
    f1 = Fraction(3, 2);
    f2 = Fraction(0, 3);
    result = (f1 - f2).toString();
    Test("Subtraction of zero", "3/2", result);
    
    //Subtraction results in zero
    f1 = Fraction(3, 2);
    f2 = Fraction(6, 4);
    result = (f1 - f2).toString();
    Test("Subtraction results in zero", "0", result);
}

void TestMultiply()
{
    std::string result = "";
    Fraction f1(4, 6);
    Fraction f2(3, 4);
    
    // Should result in 1/2
    Fraction f3 = f1.times(f2);
    result = f3.toString();
    Test( "Multiplication of non-reduced", "1/2", result );
    
    //multiplication of zero    f1 = Fraction(3, 2);
    f1 = Fraction(3, 2);
    f2 = Fraction(0, 4);
    result = (f1 * f2).toString();
    Test( "Multiplication of zero", "0", result);
    
    //multiplication of negative
    f1 = Fraction(4, 6);
    f2 = Fraction(-3, 4);
    result = (f1*f2).toString();
    Test( "Multiplication of zero", "-1/2", result);
    
    
}

void TestDivide()
{
    std::string result = "";
    Fraction f1(4, 6);
    Fraction f2(3, 4);
    
    // Should result in 16/18 -> 8/9
    Fraction f3 = f1.dividedBy(f2);
    result = f3.toString();
    Test( "Division of non-reduced", "8/9", result );
    
    //dividsion of negative
    f1 = Fraction(4, 6);
    f2 = Fraction(-3, 4);
    result = (f1/f2).toString();
    Test( "Multiplication of zero", "-8/9", result);
}

void TestEqualsAndVariations()
{
    //Test normal equals
    std::string result = "";
    Fraction f1(4, 6);
    Fraction f2(4, 6);
    Test("Normal equality", f1 == f2);
    
    f2 = Fraction(5, 6);
    Test("Normal non-equality", f1 != f2);
    
    //Test +=
    f1 = Fraction (0,2);
    f2 = Fraction (1, 2);
    Fraction resultFrac = Fraction(1,2);
    f1 += f2;
    Test("+=", f1 == resultFrac);
    
    //Test -=
    f1 -= f2;
    resultFrac = Fraction(0,1);
    Test("-=", f1 == resultFrac);
    
    //Test *=
    f1 += f2;
    f1 *= f2;
    resultFrac = Fraction(1, 4);
    Test("*=", f1 == resultFrac);
    
    //Test /=
    f1 /= f2;
    resultFrac = Fraction(1, 2);
    Test("/=", f1 == resultFrac);
    
    //Test = = =
    f1 = Fraction(3, 4);
    resultFrac = Fraction(3,4);
    Fraction f3 = Fraction(99, 99);
    f3 = f2 = f1;
    Test("a = b = c", f1 == resultFrac && f2 == resultFrac && f3 == resultFrac);
    
    //Test += += += TODO: Get feedback on hwo to get this working
    f1 = Fraction(1, 2);
    f2 = Fraction(1, 2);
    f3 = Fraction(1, 2);
    f1 += f2 += f3;
    resultFrac = Fraction(3,2);
    Fraction resultFrac2 = Fraction(2, 2);
    Fraction resultFract3 = Fraction(1, 2);
    Test("a += b += c", f1 == resultFrac && f2 == resultFrac2 && f3 == resultFract3);
}

int main()
{
    // Break up the tests into categories for better readability.
    TestConstructors();
    TestNegative();
    TestReduced();
    TestReciprocal();
    TestToDouble();
    TestPlus();
    
    Test("Approximating pi", 3.141592, ComputePi());
    
    TestMinus();
    TestMultiply();
    TestDivide();
    TestEqualsAndVariations();
    
    // TODO: Add your own additional tests
    
}
