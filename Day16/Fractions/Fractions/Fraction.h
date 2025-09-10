//
//  Fraction.h
//  Fractions
//
//  Created by Jonathan Pulsipher on 9/10/25.
//

#ifndef FRACTION_H
#define FRACTION_H

#include <string>
using std::string;

class Fraction{
private:
    //Numerator
    //
    long n;
    
    //Denominator
    //
    long d;
    
    /*
     * Reduce
     */
    void reduce();
    
    /*
     * Greatest Common Denominator
     */
    long GCD(long a, long b);
    
public:
    //By the rule of three, these contructors be
    Fraction();
    ~Fraction();
    Fraction(Fraction & copy);
    
    /*
     * Fractions are reduced. Negative values are, by convention, stored in numerator.
     */
    Fraction(long n, long d);
    
    /*
     * Find the greatest common denominator of the two denominators, set them to that, then add the numerators.
     */
    Fraction plus(Fraction rhs);
    
    /*
     * Find the greatest common denominator of the two denominators, set them to that, then subtract the numerators.
     */
    Fraction minus(Fraction rhs);
    
    /*
     * Find the greatest common denominator of the two denominators, set them to that, then add the numerators.
     */
    Fraction times(Fraction rhs);
    
    /*
     * Multiply by the rhs inverted
     */
    Fraction dividedBy(Fraction rhs);
    
    /*
     * For x/y, returns the reciprocal: y/x
     */
    Fraction reciprocal();
    
    /*
     * Returns string in format "<numerator>/<denominator>"
     */
    string toString();
    
    /*
     * Returns double of fraction
     */
    double toDouble();
    
    /*
     * Operator Overloads
     */
    Fraction operator +(Fraction& rhs);
    void operator +=(Fraction& rhs);
    Fraction operator -(Fraction& rhs);
    void operator -=(Fraction& rhs);
    Fraction operator *(Fraction& rhs);
    void operator *=(Fraction& rhs);
    Fraction operator /(Fraction& rhs);
    void operator /=(Fraction& rhs);
    bool operator ==(Fraction& rhs);
    bool operator !=(Fraction& rhs);
    bool operator <(Fraction& rhs);
    bool operator >(Fraction& rhs);
    bool operator <=(Fraction& rhs);
    bool operator >=(Fraction& rhs);
    
    long getNumerator();

    long getDenominator();

};

#endif
