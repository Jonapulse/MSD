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
