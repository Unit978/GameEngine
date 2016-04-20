#ifndef MATRIX2_H
#define MATRIX2_H

#include "SquareMatrix.h"


class Matrix2 : public SquareMatrix<2>
{
public:
    Matrix2();
    Matrix2(const SquareMatrix<2>&);

    float determinant() const;
};

typedef SquareMatrix<2> Mat2;
typedef SquareMatrix<2> mat2;

#endif // MATRIX2_H
