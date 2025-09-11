//
//  Vector.cpp
//  DIYVector
//
//  Created by Jonathan Pulsipher on 9/9/25.
//

#include "Vector.h"

Vector::Vector(int initialCapacity)
{
    array = new int[initialCapacity];
    capacity = initialCapacity;
    size = 0;
}

Vector::Vector(const Vector& myVec)
{
    this->capacity = myVec.capacity;
    this->size = myVec.size;
    int* newSpace = new int[myVec.capacity];
    for(int i = 0; i < myVec.size; i++)
        *(newSpace + i) = *(array + i);
}

Vector::~Vector(){
    freeVector();
}

void Vector::freeVector(){
    delete [] array;
}

void Vector::pushBack(int value){
    if(size + 1 > capacity)
        growVector();
    *(array + size) = value;
    size++;
}

int Vector::popBack(){
    if(size == 0)
        //TODO: implement error code
        return -1;
    int popVal = *(array + size - 1);
    size--;
    return popVal;
}

int Vector::get(int index) const
{
    return *(array + index);
}

void Vector::set(int index, int newValue)
{
    *(array + index) = newValue;
}

void Vector::growVector()
{
    capacity *= 2;
    int* newSpace = new int[capacity];
    for(int i = 0; i < size; i++)
        *(newSpace + i) = *(array + i);
    freeVector();
    array = newSpace;
}

int Vector::GetSize() const{
    return size;
}

int Vector::GetCapacity() const
{
    return capacity;
}

int& Vector::operator[](const int index) {
    return *(array + index);
}

int Vector::operator[](const int index) const{
    return get(index);
}

void Vector::operator=(const Vector& rhs)
{
    this->array = rhs.array;
    this->capacity = rhs.capacity;
    this->size = rhs.size;
}
