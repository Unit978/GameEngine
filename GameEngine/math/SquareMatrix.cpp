#include "SquareMatrix.h"

template<unsigned size>
SquareMatrix<size>::SquareMatrix()
{}

template<unsigned size>
void SquareMatrix<size>::identity(){
    for(unsigned row = 0; row < size; row++)
        for(unsigned col = 0; col < size; col++)
            elements[row][col] = row == col? 1 : 0;
}

template<unsigned size>
SquareMatrix<size> SquareMatrix<size>::inverse() const{
    float det = determinant();

    // Invertible elementsrix
    if (det != 0)
        return adjugate() * (1 / det);

    return SquareMatrix();
}

template<unsigned size>
SquareMatrix<size> SquareMatrix<size>::adjugate() const{
    return cofactorMatrix().transpose();
}

template<unsigned size>
SquareMatrix<size> SquareMatrix<size>::cofactorMatrix() const{
    SquareMatrix tmp;
    for (unsigned r = 0; r < size; ++r)
        for (unsigned c = 0; c < size; ++c)
            tmp.elements[r][c] = cofactor(r, c);
    return tmp;
}

template<unsigned size>
SquareMatrix<size> SquareMatrix<size>::transpose() const{
    SquareMatrix tmp;
    Vector<size> col;

    for(unsigned i = 0; i < size; i++){
        getCol(i, col);
        tmp.setRow(i, col);
    }

    return tmp;
}

template<unsigned size>
SquareMatrix<size-1> SquareMatrix<size>::subMatrixMinor(unsigned row, unsigned col) const{

    SquareMatrix<size-1>  tmp;

    // iterators for the tmp elementsrix
    unsigned i, j;

    // collect elements that are not part of the row and col
    i = 0;
    for (unsigned r = 0; r < size; ++r){

        // skip row in common
        if (r == row) continue;

        j = 0;
        for (unsigned c = 0; c < size; ++c){

            // skip column in common
            if (c == col) continue;

            tmp.setElement(i, j, elements[r][c]);

            // next col for the minor
            ++j;
        }

        //next row for the minor
        ++i;
    }
    return tmp;
}

template<unsigned size>
int SquareMatrix<size>::cofactorSign(unsigned row, unsigned col) const{

    // if the sum of row and col is odd then cofactor is -1
    // if the sum of row and col is even then cofactor is 1
    return (row + col) % 2 == 0 ? 1 : -1;
}

template<unsigned size>
float SquareMatrix<size>::cofactor(unsigned row, unsigned col) const{
    float minor = subMatrixMinor(row, col).determinant();
    return minor * cofactorSign(row, col);
}

template<unsigned size>
void SquareMatrix<size>::setElement(unsigned row, unsigned col, float value){
    elements[row][col] = value;
}

template<unsigned size>
void SquareMatrix<size>::setRow(unsigned row, const Vector<size>& values){
    for(unsigned i = 0; i < size; i++)
        elements[row][i] = values[i];
}

template<unsigned size>
void SquareMatrix<size>::setCol(unsigned col, const Vector<size>& values){
    for(unsigned i = 0; i < size; i++)
        elements[i][col] = values[i];
}

template<unsigned size>
float SquareMatrix<size>::getElement(unsigned row, unsigned col) const{
     return elements[row][col];
}

template<unsigned size>
void SquareMatrix<size>::getRow(unsigned row, Vector<size>& dst) const{
    for(unsigned i = 0; i < size; i++)
        dst[i] = elements[row][i];
}

template<unsigned size>
void SquareMatrix<size>::getCol(unsigned col, Vector<size>& dst) const{
    for(unsigned i = 0; i < size; i++)
        dst[i] = elements[i][col];
}

// Return the address of the first element in the elementsrix
template<unsigned size>
const float* SquareMatrix<size>::getFirstAddr() const{
    return &elements[0][0];
}

template<unsigned size>
bool SquareMatrix<size>::operator==(const SquareMatrix& other) const{
    for (unsigned r = 0; r < size; ++r)
        for (unsigned c = 0; c < size; ++c)
            if (elements[r][c] != other[r][c])
                return false;
    return true;
}

template<unsigned size>
bool SquareMatrix<size>::operator!=(const SquareMatrix& other) const{
    return !(*this==other);
}

template<unsigned size>
const SquareMatrix<size>& SquareMatrix<size>::operator=(const SquareMatrix& rhs)
{
    if (this == &rhs) return *this; // handle self assignment

    for (unsigned r = 0; r < size; ++r)
        for (unsigned c = 0; c < size; ++c)
            elements[r][c] = rhs[r][c];

    //assignment operator
    return *this;
}

template<unsigned size>
SquareMatrix<size> SquareMatrix<size>::operator+(const SquareMatrix& other) const{
    SquareMatrix tmp;
    for (unsigned r = 0; r < size; ++r)
        for (unsigned c = 0; c < size; ++c)
            tmp[r][c] = elements[r][c] + other[r][c];
    return tmp;
}

template<unsigned size>
SquareMatrix<size> SquareMatrix<size>::operator-(const SquareMatrix& other) const{
    SquareMatrix tmp;
    for (unsigned r = 0; r < size; ++r)
        for (unsigned c = 0; c < size; ++c)
            tmp[r][c] = elements[r][c] - other[r][c];
    return tmp;
}

template<unsigned size>
SquareMatrix<size> SquareMatrix<size>::operator*(const SquareMatrix& other) const{
    SquareMatrix tmp;
    Vector<size> row, col;
    for (unsigned r = 0; r < size; ++r){
        getRow(r, row);

        for(unsigned c = 0; c < size; ++c){
            other.getCol(c, col);
            tmp.elements[r][c] = row.dot(col);
        }
    }
    return tmp;
}

template<unsigned size>
SquareMatrix<size> SquareMatrix<size>::operator*(float scale) const{
    SquareMatrix tmp;
    for (unsigned r = 0; r < size; ++r)
        for (unsigned c = 0; c < size; ++c)
            tmp[r][c] = elements[r][c] * scale;
    return tmp;
}

template<unsigned size>
Vector<size> SquareMatrix<size>::operator*(const Vector<size>& v) const{
    Vector<size> tmp, row;

    for(unsigned i = 0; i < size; i++){
        getRow(i, row);
        tmp[i] = row.dot(v);
    }

    return tmp;
}

template<unsigned size>
const SquareMatrix<size>& SquareMatrix<size>::operator+=(const SquareMatrix& other){
    for (unsigned r = 0; r < size; ++r)
        for (unsigned c = 0; c < size; ++c)
            elements[r][c] += other[r][c];
    return *this;
}

template<unsigned size>
const SquareMatrix<size>& SquareMatrix<size>::operator-=(const SquareMatrix& other){
    for (unsigned r = 0; r < size; ++r)
        for (unsigned c = 0; c < size; ++c)
            elements[r][c] -= other[r][c];
    return *this;
}

template<unsigned size>
const SquareMatrix<size>& SquareMatrix<size>::operator*=(const SquareMatrix& other){
    Vector<size> row, col;
    for (unsigned r = 0; r < size; ++r){
        this->getRow(r, row);
        for(unsigned c = 0; c < size; ++c){
            other.getCol(c, col);
            elements[r][c] = row.dot(col);
        }
    }
    return *this;
}

template<unsigned size>
const SquareMatrix<size>& SquareMatrix<size>::operator*=(float scale){
    for (unsigned r = 0; r < size; ++r)
        for (unsigned c = 0; c < size; ++c)
            elements[r][c] *= scale;
    return *this;
}

template<unsigned size>
float* SquareMatrix<size>::operator[](int index){
    return elements[index];
}

template<unsigned size>
const float* SquareMatrix<size>::operator[](int index) const{
    return elements[index];
}

template class SquareMatrix<2>;
template class SquareMatrix<3>;
template class SquareMatrix<4>;








