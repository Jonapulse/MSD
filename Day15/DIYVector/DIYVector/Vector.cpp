//
//  Vector.cpp
//  DIYVector
//
//  Created by Jonathan Pulsipher on 9/9/25.
//

#include "Vector.h"


Vector::Vector(int initialCapacity)
{
    arr = new int[initialCapacity];
    capacity = initialCapacity;
    size = 0;
}

Vector::Vector(const Vector& myVec)
{
    this->capacity = myVec.capacity;
    this->size = myVec.size;
    int* newSpace = new int[myVec.capacity];
    for(int i = 0; i < myVec.size; i++)
        *(newSpace + i) = *(arr + i);
}

Vector::~Vector(){
    freeVector();
}

void Vector::freeVector(){
    delete [] arr;
}

void Vector::pushBack(int value){
    if(size + 1 > capacity)
        growVector();
    *(arr + size) = value;
    size++;
}

int Vector::popBack(){
    if(size == 0)
        //TODO: implement error code
        return -1;
    int popVal = *(arr + size - 1);
    size--;
    return popVal;
}

int Vector::get(int index) const
{
    return *(arr + index);
}

void Vector::set(int index, int newValue)
{
    *(arr + index) = newValue;
}

void Vector::growVector()
{
    capacity *= 2;
    int* newSpace = new int[capacity];
    for(int i = 0; i < size; i++)
        *(newSpace + i) = *(arr + i);
    freeVector();
    arr = newSpace;
}

int Vector::GetSize() const{
    return size;
}

int Vector::GetCapacity() const
{
    return capacity;
}

int& Vector::operator[](const int index) {
    return *(arr + index);
}

int Vector::operator[](const int index) const{
    return get(index);
}

void Vector::operator=(const Vector& rhs)
{
    this->arr = rhs.arr;
    this->capacity = rhs.capacity;
    this->size = rhs.size;
}
