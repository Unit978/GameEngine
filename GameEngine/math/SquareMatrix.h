#ifndef SQUAREMATRIX_H
#define SQUAREMATRIX_H

#include <ostream>
#include "Vector.h"

using std::ostream;

/**
    A general mathematical square matrix.
*/

// Size corresponds to the Nth dimension for the NxN square matrix.
template<unsigned size>
class SquareMatrix {

// Print out the matrix, row by row.
friend ostream& operator<<(ostream& os, const SquareMatrix& m){

    for(unsigned row = 0; row < size; row++) {

        os << '[';
        for (unsigned col = 0; col < size; col++){

            os << m[row][col];
            if (col < size - 1)
                os << ", ";
        }

        os << ']';
        if (row < size - 1)
            os << '\n';
    }
    return os;
}

public:
    SquareMatrix();

    void identity();

    float determinant() const { return 0; };
    SquareMatrix inverse() const;
    SquareMatrix adjugate() const;
    SquareMatrix cofactorMatrix() const;
    SquareMatrix transpose() const;

    // Generate the sub matrix minor at the specified row and column
    SquareMatrix<size-1> subMatrixMinor(unsigned row, unsigned col) const;

    int cofactorSign(unsigned row, unsigned col) const;
    float cofactor(unsigned row, unsigned col) const;

    // Set the value of the matrix element at specified row and column position
    void setElement(unsigned, unsigned, float);

    // Set the values of the row
    void setRow(unsigned, const Vector<size>&);

    // Set the values of the column
    void setCol(unsigned, const Vector<size>&);

    float getElement(unsigned row, unsigned col) const;
    void getRow(unsigned row, Vector<size>&) const;
    void getCol(unsigned col, Vector<size>&) const;

    // Gets the address of the first matrix element.
    const float* getFirstAddr() const;

    bool operator==(const SquareMatrix&) const;
    bool operator!=(const SquareMatrix&) const;
    const SquareMatrix& operator=(const SquareMatrix&);
    SquareMatrix operator+(const SquareMatrix&) const;
    SquareMatrix operator-(const SquareMatrix&) const;
    SquareMatrix operator*(const SquareMatrix&) const;
    SquareMatrix operator*(float scale) const;

    // Multiplication with a Vector<size>. The vector is interpreted as a sizex1 matrix.
    Vector<size> operator*(const Vector<size>&) const;

    const SquareMatrix& operator+= (const SquareMatrix&);
    const SquareMatrix& operator-= (const SquareMatrix&);
    const SquareMatrix& operator*= (const SquareMatrix&);
    const SquareMatrix& operator*=(float);

    float* operator[](int index);
    const float* operator[](int index) const;

    float elements[size][size];

};

#endif // SQUAREMATRIX_H
