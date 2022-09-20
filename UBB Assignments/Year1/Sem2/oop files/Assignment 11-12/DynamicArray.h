#pragma once

#include "Domain.h"

typedef Event TElem;

template <typename T>
class DynamicVector
{
private:
	T* elems;
	int capacity, size = 0;

public:
	// constructors
	explicit DynamicVector(int capacity = 10);
	DynamicVector(const DynamicVector& v);

	DynamicVector& operator=(const DynamicVector& v);
	DynamicVector& operator+(const T& elem);
	void add(const T elem);
	void resize();
	int find(const T& elem);
	void remove(const T& elem);

	T& operator[](int index); // { return this->elems[index]; }

	int getSize() const { return this->size; }

	~DynamicVector();
};

template <typename T>
DynamicVector<T>::DynamicVector(int capacity) : size{ 0 }, capacity{ capacity }
{
    this->elems = new T[capacity];
}

template <typename T>
DynamicVector<T>::DynamicVector(const DynamicVector<T>& v)
{
    this->size = v.size;
    this->capacity = v.capacity;
    this->elems = new T[this->capacity];
    for (int i = 0; i < this->size; i++)
        this->elems[i] = v.elems[i];
}

template <typename T>
DynamicVector<T>& DynamicVector<T>::operator=(const DynamicVector<T>& v)
{
    if (this == &v)
        return *this;

    this->capacity = v.capacity;
    this->size = v.size;

    delete[] this->elems;
    this->elems = new T[this->capacity];
    for (int i = 0; i < this->size; i++)
        this->elems[i] = v.elems[i];

    return *this;
}

template <typename T>
DynamicVector<T>& DynamicVector<T>::operator+(const T& elem)
{
    if (this->size == this->capacity)
        this->resize();
    this->elems[this->size++] = elem;
    return *this;
}

template <typename T>
T& DynamicVector<T>::operator[](int pos)
{
    return this->elems[pos];
}

template <typename T>
DynamicVector<T>::~DynamicVector()
{
    delete[] this->elems;
}

template <typename T>
void DynamicVector<T>::resize() {
    this->capacity += 10;
    TElem* newElems = new T[this->capacity];
    for (int i = 0; i < this->size; i++)
        newElems[i] = this->elems[i];

    delete[] this->elems;
    this->elems = newElems;
}

template <typename T>
int DynamicVector<T>::find(const T& elem) {
    for (int i = 0; i < this->size; i++)
        if (this->elems[0].getTitle() == elem.getTitle())
            return i;
    return -1;
}

template <typename T>
void DynamicVector<T>::add(const T elem) {
    if (this->size == this->capacity)
        this->resize();
    this->elems[this->size++] = elem;
}

template <typename T>
void DynamicVector<T>::remove(const T& elem) {
    int iteratorWhereElemIsFound = this->find(elem);
    if (iteratorWhereElemIsFound == -1)
        return;
//    delete this->elems[iteratorWhereElemIsFound];
    for (int i = iteratorWhereElemIsFound; i < this->size - 1; i++)
        this->elems[i] = this->elems[i + 1];
    this->size--;
}

