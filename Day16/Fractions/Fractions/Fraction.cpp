//
//  Fraction.cpp
//  Fractions
//
//  Created by Jonathan Pulsipher on 9/10/25.
//

#include "Fraction.h"

//Numerator
//
long n;

//Denominator
//
long d;

/*
 * Reduce
 */
void Fraction::reduce()
{
    //TODO: implement
}

/*
 * Greatest Common Denominator
 */
long Fraction::GCD()
{
    //TODO: implement
    return 0;
}

Fraction::Fraction(){
    //TODO: implement
}

Fraction::Fraction(long n, long d)
{
    this->n = n;
    this->d = d;
    
    reduce();
    
    //If denominator is negative, move it to the numerator (or make both positive)
    if(this->d < 0)
    {
        this->d *= -1;
        this->n *= -1;
    }
}

Fraction Fraction::plus(Fraction rhs){
    //TODO: implement
    return Fraction{};
}

Fraction Fraction::minus(Fraction rhs){
    //TODO: implement
    return Fraction{};
}

Fraction Fraction::times(Fraction rhs){
    //TODO: implement
    return Fraction{};
}

Fraction Fraction::dividedBy(Fraction rhs){
    //TODO: implement
    return Fraction{};
}

Fraction Fraction::reciprocal(){
    //TODO: implement
    return Fraction{};
}

string Fraction::toString(){
    //TODO: implement
    return "";
}

double Fraction::toDouble(){
    //TODO: implement
    return 0;
}

Fraction::~Fraction(){
    //TODO: implement
}
