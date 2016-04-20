#include "Matrix2.h"

Matrix2::Matrix2()
{
    //ctor
}

Matrix2::Matrix2(const SquareMatrix<2>& other){
    for(unsigned row = 0; row < 2; row++)
        for(unsigned col = 0; col < 2; col++)
            elements[row][col] = other[row][col];
}

float Matrix2::determinant() const{
    float a, b, c, d;
    a = elements[0][0];
    b = elements[0][1];
    c = elements[1][0];
    d = elements[1][1];
    return a*d - c*b;
}
