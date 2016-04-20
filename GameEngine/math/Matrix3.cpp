#include "Matrix3.h"

#include <cmath>

Matrix3::Matrix3()
{
    //ctor
}

Matrix3::Matrix3(const SquareMatrix<3>& other){
    for(unsigned row = 0; row < 3; row++)
        for(unsigned col = 0; col < 3; col++)
            elements[row][col] = other[row][col];
}

float Matrix3::determinant() const{
    float a, b, c, d, e, f, g, h, i;
    a = elements[0][0];
    b = elements[0][1];
    c = elements[0][2];

    d = elements[1][0];
    e = elements[1][1];
    f = elements[1][2];

    g = elements[2][0];
    h = elements[2][1];
    i = elements[2][2];

    return (a*e*i) - (a*f*h) - (b*d*i) + (b*f*g) + (c*d*h) - (c*e*g);
}


Matrix3 Matrix3::translation(const Vector2& translation){
    Matrix3 tmp;
    tmp.setElement(0, 2, translation.x);
    tmp.setElement(1, 2, translation.y);
    return tmp;
}

Matrix3 Matrix3::rotation(const Radians& rad){
    Matrix3 tmp;

    float c = cosf(rad.value);
    float s = sinf(rad.value);

    tmp.setElement(0, 0, c);
    tmp.setElement(0, 1, -s);
    tmp.setElement(1, 0, s);
    tmp.setElement(1, 1, c);

    return tmp;
}

Matrix3 Matrix3::rotation(const Degrees& deg){
    return rotation(Radians(deg));
}

Matrix3 Matrix3::scale(const Vector2& scale){
    Matrix3 tmp;
    tmp.setElement(0, 0, scale.x);
    tmp.setElement(1, 1, scale.y);
    return tmp;
}

Matrix3 Matrix3::shear(const Vector2& shear){
    Matrix3 tmp;
    tmp.setElement(0, 1, shear.x);
    tmp.setElement(1, 0, shear.y);
    return tmp;
}
