//
//  Untitled.h
//  DIYVector
//
//  Created by Jonathan Pulsipher on 9/9/25.
//

#ifndef VECTOR_H
#define VECTOR_H

struct Vector{
    int* array;
    int capacity;
    int size;
}

Vector makeVector(int initialCapacity);

#endif
