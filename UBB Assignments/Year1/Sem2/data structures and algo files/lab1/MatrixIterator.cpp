//
// Created by bia on 09/04/2022.
//

#include "Matrix.h"
#include "MatrixIterator.h"

using namespace std;


MatrixIterator::MatrixIterator(const Matrix& m) : matrix(m){}
    /// ignore this, it's likely not right
//{
//    this->currentRow = 0;
//    this->lineIndexStart = 0;
//    this->lineIndexEnd = this->matrix.nrRows;
//    int found = 1;
//    int foundEnd = 1;
//
//    for(int i = 0; i < this->matrix.nrRows - 1; i++)
//        // find the first populated row and initialise lineIndexStart with its index
//        if (this->matrix.rowCounter[i + 1] != 0  && found == 1) {
//            this->lineIndexStart = i;
//            found = 0;
//        }
//
//    for(int i = this->matrix.nrRows; i > 0; i--)
//        // find the last populated row and initialise lineIndexEnd with its index
//            if (this->matrix.rowCounter[i] != this->matrix.rowCounter[i - 1] && foundEnd == 1){
//                this->lineIndexEnd = i;
//                foundEnd = 0;
//                break;
//            }
//
//    this->currentRow = this->lineIndexStart;
//}
/// theta(1)


void MatrixIterator::first() {
    this->current = 0;
}
/// theta(1)


void MatrixIterator::next() {
    this->current++;
    // if it reaches the end it starts again from the beginning
    if (!valid())
        this->current = 0;
}
/// theta(1)


TElem MatrixIterator::getCurrent(){
    return this->matrix.nonzeroElements[this->current];
}
/// theta(1)


bool MatrixIterator::valid() const {
    if (this->current >= this->matrix.capacity) return false;
    return true;
}
/// theta(1)
