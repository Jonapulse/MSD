//
//  Untitled.h
//  DIYVector
//
//  Created by Jonathan Pulsipher on 9/9/25.
// W/ Alexis, Badr, Demi, Dylan, Fatima
//

#ifndef VECTOR_H
#define VECTOR_H

class Vector{
private:
    int* arr;
    int capacity;
    int size;
    
    void growVector();
    void freeVector();
    
public:
    Vector (int capacity);
    Vector (const Vector& vec);
    void pushBack(int value);
    int popBack();
    int get(int index) const;
    void set(int index, int newValue);
    int GetSize() const;
    int GetCapacity() const;
    
    void operator=(const Vector& rhs);
    int& operator[](const int index);
    int operator[](const int index) const;
    
    ~Vector();
};

#endif
