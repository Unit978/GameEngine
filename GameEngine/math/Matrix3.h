#ifndef MATRIX3_H
#define MATRIX3_H

#include "SquareMatrix.h"
#include "Vector2.h"

#include "MathUtil.h"
#include "MeasurementUnits.h"

class Matrix3 : public SquareMatrix<3>
{
public:
    Matrix3();
    Matrix3(const SquareMatrix<3>&);

    float determinant() const;

    /* Transformation matrices for 2D operations */

    // Obtains a translation matrix for 2D transformations.
    static Matrix3 translation(const Vector2&);

    // This is rotation around the Z - axis for the X/Y 2D plane
    // The Rad/Deg in the function name is to determine the angle type
    // which can radians or degrees for rotation.
    static Matrix3 rotation(const Degrees&);
    static Matrix3 rotation(const Radians&);

    static Matrix3 scale(const Vector2&);
    static Matrix3 shear(const Vector2&);

};

typedef SquareMatrix<3> Mat3;
typedef SquareMatrix<3> mat3;

#endif // MATRIX3_H
