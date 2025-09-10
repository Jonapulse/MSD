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
    long GCD();
    
public:
    Fraction();
    /*
     * Fractions are reduced. Negative values are, by convention, stored in numerator.
     */
    Fraction(long n, long d);
    Fraction plus(Fraction rhs);
    Fraction minus(Fraction rhs);
    Fraction times(Fraction rhs);
    Fraction dividedBy(Fraction rhs);
    Fraction reciprocal();
    string toString();
    double toDouble();
    ~Fraction();
    
};

#endif
