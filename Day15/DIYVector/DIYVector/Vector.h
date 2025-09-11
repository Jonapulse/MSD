//
//  Untitled.h
//  DIYVector
//
//  Created by Jonathan Pulsipher on 9/9/25.
// W/ Alexis, Badr, Demi, Dylan, Fatima
//

#ifndef VECTOR_H
#define VECTOR_H

template <typename T>
class Vector{
private:
    T* arr;
    int capacity;
    int size;
    
    void growVector();
    void freeVector();
    
public:
    Vector();
    Vector (int capacity);
    Vector (const Vector& vec);
    void pushBack(T value);
    T popBack();
    T get(int index) const;
    void set(int index, T newValue);
    int GetSize() const;
    int GetCapacity() const;
    
    void operator=(const Vector& rhs);
    T& operator[](const int index);
    T operator[](const int index) const;
    
    ~Vector();
};

//Empty Vector defaults to 10
template <typename T>
Vector<T>::Vector()
{
    arr = new T[1];
    size = 0;
    capacity = 1;
}

template <typename T>
Vector<T>::Vector(int initialCapacity)
{
    arr = new int[initialCapacity];
    capacity = initialCapacity;
    size = 0;
}

template <typename T>
Vector<T>::Vector(const Vector& myVec)
{
    this->capacity = myVec.capacity;
    this->size = myVec.size;
    T* newSpace = new T[myVec.capacity];
    for(int i = 0; i < myVec.size; i++)
        *(newSpace + i) = *(arr + i);
}

template <typename T>
Vector<T>::~Vector(){
    freeVector();
}

template <typename T>
void Vector<T>::freeVector(){
    delete [] arr;
}

template <typename T>
void Vector<T>::pushBack(T value){
    if(size + 1 > capacity)
        growVector();
    *(arr + size) = value;
    size++;
}

template <typename T>
T Vector<T>::popBack(){
    if(size == 0)
        //TODO: implement error code
        return -1;
    T popVal = *(arr + size - 1);
    size--;
    return popVal;
}

template <typename T>
T Vector<T>::get(int index) const
{
    return *(arr + index);
}

template <typename T>
void Vector<T>::set(int index, T newValue)
{
    *(arr + index) = newValue;
}

template <typename T>
void Vector<T>::growVector()
{
    capacity *= 2;
    T* newSpace = new T[capacity];
    for(int i = 0; i < size; i++)
        *(newSpace + i) = *(arr + i);
    freeVector();
    arr = newSpace;
}

template <typename T>
int Vector<T>::GetSize() const{
    return size;
}

template <typename T>
int Vector<T>::GetCapacity() const
{
    return capacity;
}

template <typename T>
T& Vector<T>::operator[](const int index) {
    return *(arr + index);
}

template <typename T>
T Vector<T>::operator[](const int index) const{
    return get(index);
}

template <typename T>
void Vector<T>::operator=(const Vector& rhs)
{
    this->arr = rhs.arr;
    this->capacity = rhs.capacity;
    this->size = rhs.size;
}

#endif
