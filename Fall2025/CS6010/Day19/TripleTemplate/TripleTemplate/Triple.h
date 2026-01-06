//
//  Triple.h
//  TripleTemplate
//
//  Created by Jonathan Pulsipher on 9/11/25.
//

#ifndef TRIPLE_H
#define TRIPLE_H

template <typename T>
class Triple{
private:
    T a;
    T b;
    T c;
    
public:
    Triple(T a, T b, T c);
    ~Triple();
    
    T getA();
    T getB();
    T getC();
    T SumTriple();
};

template <typename T>
Triple<T>::Triple(T a, T b, T c)
{
    this->a = a;
    this->b = b;
    this->c = c;
}

template <typename T>
Triple<T>::~Triple(){}

template <typename T>
T Triple<T>::getA()
{
    return a;
}

template <typename T>
T Triple<T>::getB()
{
    return b;
}

template <typename T>
T Triple<T>::getC()
{
    return c;
}

template <typename T>
T Triple<T>::SumTriple()
{
    return a + b + c;
}


#endif
