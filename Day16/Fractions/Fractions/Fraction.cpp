//
//  Fraction.cpp
//  Fractions
//
//  Created by Jonathan Pulsipher on 9/10/25.
//

#include "Fraction.h"
#include <cmath>

//Constructors/Destructors
Fraction::Fraction(){
    n = 0;
    d = 1; //By convention, to avoid divide-by-zero
}

Fraction::Fraction(Fraction & copy){
    this->n = copy.getNumerator();
    this->d = copy.getDenominator();
}

Fraction::~Fraction(){}

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
    long gcd = GCD(n, d);
    n /= gcd;
    d /= gcd;
}

/*
 *If denominator is negative, move it to the numerator (or make both positive) NOTE: You could combine the below code into a 'normalize' function;
 */
void Fraction::normalize()
{
    if(this->d < 0)
    {
        this->d *= -1;
        this->n *= -1;
    }
}

/*
 * Greatest Common Denominator
 */
long Fraction::GCD(long a, long b)
{
    long gcd = abs(a);
    long remainder = abs(b);
    while(remainder != 0) {
      long temp = remainder;
      remainder = gcd % remainder;
      gcd = temp;
    }
    return gcd;
}

Fraction::Fraction(long n, long d)
{
    this->n = n;
    this->d = d;
    
    reduce();
    normalize();
}

Fraction Fraction::plus(Fraction rhs) const{
    long denominatorProduct = this->d * rhs.d;
    long new_n = this->n * rhs.d + rhs.n * this->d;
    long new_d = denominatorProduct;
    return Fraction{new_n, new_d};
}

Fraction Fraction::minus(Fraction rhs) const{
    long denominatorProduct = this->d * rhs.d;
    long new_n = this->n * rhs.d - rhs.n * this->d;
    long new_d = denominatorProduct;
    return Fraction{new_n, new_d};
}

Fraction Fraction::times(Fraction rhs) const{
    return Fraction{this->n * rhs.n, this->d * rhs.d};
}

Fraction Fraction::dividedBy(Fraction rhs) const{
    return (*this).times(rhs.reciprocal());
}

Fraction Fraction::reciprocal() const{
    long recN = this->d;
    long recD = this->n;
    return Fraction{recN, recD};
}

string Fraction::toString() const{
    if(n == 0) //For zero
        return "0";
    else if( d == 1) //For whole numbers
        return std::to_string(n);
    else
        return std::to_string(n) + "/" + std::to_string(d);
}

double Fraction::toDouble() const{
    return n/(double)d;
}

long Fraction::getNumerator() const{
    return n;
}

long Fraction::getDenominator() const{
    return d;
}

/*
 * Operator Overloads
 */
Fraction Fraction::operator +(Fraction& rhs){
    return plus(rhs);
}
Fraction& Fraction::operator +=(Fraction& rhs)
{
    Fraction newFrac = (*this) + rhs;
    (*this) = newFrac;
    return *this;
}
Fraction Fraction::operator -(Fraction& rhs){
    return minus(rhs);
}
Fraction& Fraction::operator -=(Fraction& rhs){
    Fraction newFrac = (*this) - rhs;
    (*this) = newFrac;
    return *this;
}
Fraction Fraction::operator *(Fraction& rhs){
    return times(rhs);
}
Fraction& Fraction::operator *=(Fraction& rhs){
    Fraction newFrac = (*this) * rhs;
    (*this) = newFrac;
    return *this;
}
Fraction Fraction::operator /(Fraction& rhs){
    return dividedBy(rhs);
}
Fraction& Fraction::operator /=(Fraction& rhs) {
    Fraction newFrac = (*this) / rhs;
    (*this) = newFrac;
    return *this;
}
bool Fraction::operator ==(Fraction& rhs){
    return (this->n == rhs.n && this->d == rhs.d);
}
bool Fraction::operator !=(Fraction& rhs){
    return !((*this) == rhs);
}
bool Fraction::operator <(Fraction& rhs){
    return this->toDouble() < rhs.toDouble();
}
bool Fraction::operator >(Fraction& rhs){
    return toDouble() > rhs.toDouble();
}
bool Fraction::operator <=(Fraction& rhs){
    return toDouble() <= rhs.toDouble();
}
bool Fraction::operator >=(Fraction& rhs){
    return toDouble() >= rhs.toDouble();
}

