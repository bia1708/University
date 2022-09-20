//#include "DynamicArray.h"
//
//DynamicVector::DynamicVector(int capacity) : size{ 0 }, capacity{ capacity }
//{
//	this->elems = new TElem[capacity];
//}
//
//DynamicVector::DynamicVector(const DynamicVector& v)
//{
//	this->size = v.size;
//	this->capacity = v.capacity;
//	this->elems = new TElem[this->capacity];
//	for (int i = 0; i < this->size; i++)
//		this->elems[i] = v.elems[i];
//}
//
//DynamicVector& DynamicVector::operator=(const DynamicVector& v)
//{
//	if (this == &v)
//		return *this;
//
//	this->capacity = v.capacity;
//	this->size = v.size;
//
//	delete[] this->elems;
//	this->elems = new TElem[this->capacity];
//	for (int i = 0; i < this->size; i++)
//		this->elems[i] = v.elems[i];
//
//	return *this;
//}
//
//DynamicVector& DynamicVector::operator+(const TElem& elem)
//{
//	if (this->size == this->capacity)
//		this->resize();
//	this->elems[this->size++] = elem;
//	return *this;
//}
//
//DynamicVector::~DynamicVector()
//{
//	delete[] this->elems;
//}
//
//void DynamicVector::resize() {
//	this->capacity += 10;
//	TElem* newElems = new TElem[this->capacity];
//	for (int i = 0; i < this->size; i++)
//		newElems[i] = this->elems[i];
//
//	delete[] this->elems;
//	this->elems = newElems;
//}
//
//int DynamicVector::find(const TElem& elem) {
//	for (int i = 0; i < this->size; i++)
//		if (this->elems[0].getTitle() == elem.getTitle())
//			return i;
//	return -1;
//}
//
//void DynamicVector::add(const TElem& elem) {
//	if (this->size == this->capacity)
//		this->resize();
//	this->elems[this->size++] = elem;
//}
//
//void DynamicVector::remove(const TElem& elem) {
//	int iteratorWhereElemIsFound = this->find(elem);
//	if (iteratorWhereElemIsFound == -1)
//		return;
//	//delete this->elems[iteratorWhereElemIsFound];
//	for (int i = iteratorWhereElemIsFound; i < this->size - 1; i++)
//		this->elems[i] = this->elems[i + 1];
//	this->size--;
//}
