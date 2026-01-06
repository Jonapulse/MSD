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
    
    Fraction(long n, long d);
    Fraction plus(Fraction rhs) const;
    Fraction minus(Fraction rhs) const;
    Fraction times(Fraction rhs) const;
    Fraction dividedBy(Fraction rhs) const;
    Fraction reciprocal() const;
    
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
    
    string toString() const;
    double toDouble() const;

private:
    //Numerator
    //
    long n;
    
    //Denominator
    //
    long d;

    void reduce();
    // Normalize so sign (+/-) is on numerator
    void normalize();
    //Greatest Common Denominator
    long GCD(long a, long b);
};

#endif
