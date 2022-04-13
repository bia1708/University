#include "Matrix.h"
#include <exception>
using namespace std;


Matrix::Matrix(int nrLines, int nrCols) {
    this->nrRows = nrLines;
    this->nrCols = nrCols;
    this->nonzeroElements = new TElem [2 * this->nrRows];
    this->columnIndices = new int [2 * this->nrRows];
    this->capacity = 2 * this->nrRows;

    this->rowCounter = new int [this->nrRows + 1];
    for(int i = 0; i <= this->nrRows; i++)
        this->rowCounter[i] = 0;
}
/// theta(1)


Matrix::~Matrix() {
    delete[] this->nonzeroElements;
    delete[] this->columnIndices;
    delete[] this->rowCounter;
}
/// theta(1)

int Matrix::nrLines() const {
	return this->nrRows;
}
/// theta(1)


int Matrix::nrColumns() const {
	return this->nrCols;
}
/// theta(1)


TElem Matrix::element(int i, int j) const {
    if (i < 0 || i >= this->nrRows || j < 0 || j >= this->nrCols)
        throw exception();
    int rowStart = this->rowCounter[i];
    int rowEnd = this->rowCounter[i + 1];
    for (int k = rowStart; k < rowEnd; k++){
        if (this->columnIndices[k] == j)
            return this->nonzeroElements[k];
    }
	return NULL_TELEM;
}
/// BC: the element is the first one in its column -> theta(1)
/// WC: the element is the last one in its column and the column is full of non-zero elements or it does
/// not exist at all in the arrays (= 0) -> theta(nrRows)
/// AC: theta(nrRows)
/// total complexity: O(nrRows)


TElem Matrix::modify(int i, int j, TElem e) {
    if (i < 0 || i >= this->nrRows || j < 0 || j >= this->nrCols) {
        throw exception();
    }

    int rowStart = this->rowCounter[i];
    int rowEnd = this->rowCounter[i + 1];
    for (int k = rowStart; k < rowEnd; k++){
        if (this->columnIndices[k] == j) {
            TElem oldElem = this->nonzeroElements[k];
            if (e != NULL_TELEM) {
                this->nonzeroElements[k] = e;
            } else {
                int numberOfNonZeroElements = this->rowCounter[this->nrRows];
                for(int t = k; t < numberOfNonZeroElements - 1; t++){
                    this->nonzeroElements[t] = this->nonzeroElements[t + 1];
                    this->columnIndices[t] = this->columnIndices[t + 1];
                }
                /// in column pointers, all elements after the column index are decremented
                for(int t = i + 1; t <= this->nrRows; t++)
                    this->rowCounter[t]--;
            }
            return oldElem;
        }
    }
    if (e == NULL_TELEM) {
        return NULL_TELEM;
    }

    /// If the new element is non-zero, it is must be added to the representation
    /// by updating the 3 arrays.

    /// in column pointers, all elements after the column j are incremented
    for(int s = i + 1; s <= this->nrRows; s++)
        this->rowCounter[s]++;

    int newElementIndex;
    int currentIndex = rowStart;
    bool found = false;

    /// find the right position where to insert the new element
    while(!found && currentIndex < rowEnd){
        if(this->columnIndices[currentIndex] > j){
            found = true;
        }
        else currentIndex++;
    }

    newElementIndex = currentIndex;

    /// check for the need to resize (expand).
    int numberOfNonZeroElements = this->rowCounter[this->nrRows];
    if(numberOfNonZeroElements == this->capacity)
        this->resize( 2 * this->capacity);

    /// move the elements that come after the insertion index, one position to the right, in order to make room
    /// for the new element

    for(int t = numberOfNonZeroElements; t > newElementIndex; t--){
        this->nonzeroElements[t] = this->nonzeroElements[t - 1];
        this->columnIndices[t] = this->columnIndices[t - 1];
    }

    /// insert the element in the array of elements and its row index in the array of indices.
    this->nonzeroElements[newElementIndex] = e;
    this->columnIndices[newElementIndex] = j;

    return NULL_TELEM;
}
/// BC: on the given position is a non-zero element, it's the first on its column and is replaced by another non-zero
/// element -> theta(1)
/// WC: on the given position is a 0 which has to be replaced with a non-zero element, after performing a resize
/// theta(new_capacity)
/// total: O(current_capacity)


void Matrix::resize(int newCapacity){
    TElem* newArrayNonZeroElem = new TElem[newCapacity];
    int* newArrayOfColumnIndices = new int[newCapacity];

    /// if the array shrinks, we only copy the elements up until the new capacity
    if(newCapacity < this->capacity)
        for(int i = 0; i < newCapacity; i++){
            newArrayNonZeroElem[i] = this->nonzeroElements[i];
            newArrayOfColumnIndices[i] = this->columnIndices[i];
        }

        /// if the array expands, we copy all its old elements
    else
        for(int i = 0; i < this->capacity; i++){
            newArrayNonZeroElem[i] = this->nonzeroElements[i];
            newArrayOfColumnIndices[i] = this->columnIndices[i];
        }

    /// delete the old arrays
    delete[] this->nonzeroElements;
    delete[] this->columnIndices;

    /// update the new array
    this->nonzeroElements = newArrayNonZeroElem;
    this->columnIndices = newArrayOfColumnIndices;
    this->capacity = newCapacity;
}
/// theta(min(oldCapacity, newCapacity))

void Matrix::resizeMatrix(int newLines, int newCols) {
    if (newLines <= 0 || newCols <= 0) {
        exception ex;
        throw ex;
    } else if(newCols < this->nrCols || newLines < this->nrRows){
        TElem* newArrayNonZeroElem = new TElem[newCols];
        int* newArrayOfColumnIndices = new int[newCols];
        for(int i = 0; i < newCols; i++){
            newArrayNonZeroElem[i] = this->nonzeroElements[i];
            newArrayOfColumnIndices[i] = this->columnIndices[i];
        }
        for(int i = nrRows; i < this->nrRows - 1; i++)
            this->rowCounter[i] = this->rowCounter[i + 1];
    }
    this->nrRows = newLines;
    this->nrCols = newCols;
}