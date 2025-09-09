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
    int* array;
    int capacity;
    int size;
    
public:
    Vector (int capacity);
    void freeVector();
    void pushBack(int value);
    int popBack();
    int get(int index);
    void set(int index, int newValue);
    void growVector();
    int GetSize();
    int GetCapacity();
    
    ~Vector();
};



#endif
