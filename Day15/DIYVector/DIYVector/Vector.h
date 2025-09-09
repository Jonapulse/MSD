//
//  Untitled.h
//  DIYVector
//
//  Created by Jonathan Pulsipher on 9/9/25.
// W/ Alexis, Badr, Demi, Dylan, Fatima
//

#ifndef VECTOR_H
#define VECTOR_H

struct Vector{
    int* array;
    int capacity;
    int size;
};

Vector makeVector(int initialCapacity);

void freeVector(Vector vec);

void pushBack(Vector& vec, int value);

int popBack(Vector& vec);

int get(Vector vec, int index);

void set(Vector& myVec, int index, int newValue);

void growVector(Vector& vec);

#endif
