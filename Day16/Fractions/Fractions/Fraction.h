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
public:
    //By the rule of three, these contructors be
    Fraction();
    ~Fraction();
    Fraction(Fraction& copy);
    
    /*
     * Fractions are reduced. Negative values are, by convention, stored in numerator.
     */
    Fraction(long n, long d);
    
    /*
     * Find the greatest common denominator of the two denominators, set them to that, then add the numerators.
     */
    Fraction plus(Fraction rhs) const;
    
    /*
     * Find the greatest common denominator of the two denominators, set them to that, then subtract the numerators.
     */
    Fraction minus(Fraction rhs) const;
    
    /*
     * Find the greatest common denominator of the two denominators, set them to that, then add the numerators.
     */
    Fraction times(Fraction rhs) const;
    
    /*
     * Multiply by the rhs inverted
     */
    Fraction dividedBy(Fraction rhs) const;
    
    /*
     * For x/y, returns the reciprocal: y/x
     */
    Fraction reciprocal() const;
    
    /*
     * Returns string in format "<numerator>/<denominator>"
     */
    string toString() const;
    
    /*
     * Returns double of fraction
     */
    double toDouble() const;
    
    /*
     * Operator Overloads
     */
    Fraction operator +(Fraction& rhs);
    Fraction& operator +=(Fraction& rhs);
    Fraction operator -(Fraction& rhs);
    Fraction& operator -=(Fraction& rhs);
    Fraction operator *(Fraction& rhs);
    Fraction& operator *=(Fraction& rhs);
    Fraction operator /(Fraction& rhs);
    Fraction& operator /=(Fraction& rhs);
    
    bool operator ==(Fraction& rhs);
    bool operator !=(Fraction& rhs);
    bool operator <(Fraction& rhs);
    bool operator >(Fraction& rhs);
    bool operator <=(Fraction& rhs);
    bool operator >=(Fraction& rhs);
    
    long getNumerator() const;
    long getDenominator() const;

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
     * Normalize so sign (+/-) is on numerator
     */
    void normalize();
    
    /*
     * Greatest Common Denominator
     */
    long GCD(long a, long b);
};

#endif
