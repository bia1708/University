//
// Created by bia on 09/04/2022.
//
#pragma once
#include "Matrix.h"

class Matrix;

class MatrixIterator
{
    friend class Matrix;

private:
    const Matrix& matrix;
    int current = 0;
    explicit MatrixIterator(const Matrix& m);

    /// ignore this, I overcomplicated things
//    int currentRow;
//    int currentCol;
//    int elemCounter; // use this to keep track of where we are in the element list
//    int lineIndexStart;
//    int lineIndexEnd;

public:
    void first();
    void next();
    TElem getCurrent();
    bool valid() const;
};
