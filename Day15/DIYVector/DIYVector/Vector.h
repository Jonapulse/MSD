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
    /*
     * 'capacity' is reserved heap-space
     * 'size' is utilized space
     */
    int capacity;
    int size;
    
    /*
     * By convention, growVector will double the capacity
     * GrowVector is called when pushBack would exceed capacity
     */
    void growVector();
    void freeVector();
    
public:
    Vector();
    Vector (int capacity);
    Vector (const Vector& vec);
    
    void pushBack(T value);
    /*
     * popBack tracks 'removed' values with the size marker. The information in the heap is not deleted but can be overwritten
     */
    T popBack();
    T get(int index) const;
    void set(int index, T newValue);
    int GetSize() const;
    int GetCapacity() const;
    
    T& operator=(Vector rhs);
    T& operator[](const int index);
    T operator[](const int index) const;
    
    /*
     * Compares Vector<T> lexicographically, list member by list member.
     * Comparison ignores capacity, by convention.
     */
    bool operator==(const Vector<T>& rhs) const;
    bool operator!=(const Vector<T>& rhs) const;
    bool operator<(const Vector<T>& rhs) const;
    bool operator<=(const Vector<T>& rhs) const;
    bool operator>(const Vector<T>& rhs) const;
    bool operator>=(const Vector<T>& rhs) const;
    
    ~Vector();
    
    T* begin() const;
    T* end() const;
};

//Empty Vector defaults to 10
//
template <typename T>
Vector<T>::Vector()
{
    arr = new T[10];
    size = 0;
    capacity = 10;
}

template <typename T>
Vector<T>::Vector(int initialCapacity)
{
    arr = new T[initialCapacity];
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
        newSpace[i] = arr[i];
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
    arr[size++] = value;
}

template <typename T>
T Vector<T>::popBack(){
    if(size == 0)
        //TODO: implement error code
        return -1;
    T popVal = arr[size - 1];
    size--;
    return popVal;
}

template <typename T>
T Vector<T>::get(int index) const
{
    if(index >= size)
    {
        //TODO: implement error code
    }
    return arr[index];
}

template <typename T>
void Vector<T>::set(int index, T newValue)
{
    if(index >= size){
        //TODO: implement error code
    }
    arr[index] = newValue;
}

/*
 * By convenction, growVector will double the capacity
 * GrowVector is called when pushBack would exceed capacity
 */
template <typename T>
void Vector<T>::growVector()
{
    capacity *= 2;
    T* newSpace = new T[capacity];
    for(int i = 0; i < size; i++)
        newSpace[i] = arr[i];
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
    return arr[index];
}

template <typename T>
T Vector<T>::operator[](const int index) const{
    return get(index);
}

template <typename T>
T& Vector<T>::operator=(const Vector<T> rhs)
{
    std::swap(this->size, rhs.size);
    std::swap(this->arr, rhs.arr);
    
    return *this;
}

/*
 * Compares Vector<T> lexicographically, list member by list member.
 * Comparison ignores capacity, by convention.
 */
template <typename T>
bool Vector<T>::operator==(const Vector<T>& rhs) const{
    if(this->size != rhs.size)
        return false;
    for(int i = 0; i < this->size; i++)
    {
        if((*this)[i] != rhs[i])
            return false;
    }
    return true;
}

template <typename T>
bool Vector<T>::operator!=(const Vector<T>& rhs) const{
    return !((*this) == rhs);
}

template <typename T>
bool Vector<T>::operator<(const Vector<T>& rhs) const{
    for(int i = 0; i < this->size; i++)
    {
        if((*this)[i] != rhs[i])
            return (*this)[i] < rhs[i];
    }
    return false;
}

template <typename T>
bool Vector<T>::operator<=(const Vector<T>& rhs) const{
    return ((*this) == rhs || (*this) < rhs);
}

template <typename T>
bool Vector<T>::operator>(const Vector<T>& rhs) const{
    return !((*this) <= rhs);
}

template <typename T>
bool Vector<T>::operator>=(const Vector<T>& rhs) const{
    return !((*this) < rhs);
}

template <typename T>
T* Vector<T>::begin() const{
    return arr;
}

template <typename T>
T* Vector<T>::end() const{
    return arr + size;
}

#endif
