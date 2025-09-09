//
//  Vector.cpp
//  DIYVector
//
//  Created by Jonathan Pulsipher on 9/9/25.
//

#include "Vector.h"

Vector makeVector(int initialCapacity)
{
    Vector vec;
    vec.array = new int[initialCapacity];
    vec.capacity = initialCapacity;
    vec.size = 0;
    return vec;
}

void freeVector(Vector vec){
    delete [] vec.array;
}

void pushBack(Vector& vec, int value){
    if(vec.size + 1 > vec.capacity)
        growVector(vec);
    *(vec.array + vec.size) = value;
    vec.size++;
}

int popBack(Vector& vec){
    if(vec.size == 0)
        //TODO: implement error code
        return -1;
    int popVal = *(vec.array + vec.size - 1);
    vec.size--;
    return popVal;
}

int get(Vector vec, int index)
{
    return *(vec.array + index);
}

void set(Vector& myVec, int index, int newValue)
{
    *(myVec.array + index) = newValue;
}

void growVector(Vector& vec){
    vec.capacity *= 2;
    int* newSpace = new int[vec.capacity];
    for(int i = 0; i < vec.size; i++)
        *(newSpace + i) = *(vec.array + i);
    freeVector(vec);
    vec.array = newSpace;
}
