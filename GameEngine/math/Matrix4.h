#ifndef MATRIX4_H
#define MATRIX4_H

#include "SquareMatrix.h"
#include "Vector3.h"

class Matrix4 : public SquareMatrix<4>{

public:
    Matrix4();
    Matrix4(const SquareMatrix<4>&);

    float determinant() const;

    /* Transformation matrices for 3D operations */
    static Matrix4 translation(const Vector3&);

    static Matrix4 rotationRad(const Vector3&);
    static Matrix4 rotationDeg(const Vector3&);

    static Matrix4 scale(const Vector3&);
    static Matrix4 shear(const Vector3&);

    // Create a perspective matrix based on the field of view, aspect ratio,
    // the minimum distance, and the maximum distance of view.
    // The field of view is the vertical angle (in radians) which the camera sees into the world
    // The aspect ratio is the ratio between the width and height of our target (screen)
    // rectangular area to project on.
    static Matrix4 perspective(float, float, float, float);

    // Create an orthographic matrix. There is no sense of depth with this transformation.
    // The parameters are left, right, bottom, top, far, near respectively. These values are the clipping planes.
    static Matrix4 ortho(float, float, float, float, float, float);

    // Constructs a view matrix AKA look at matrix.
    // 1st param: The eye position.
    // 2nd param: The target position, what we are looking at
    // 3rd param: Up orientation (axis) relative to the eye
    static Matrix4 lookAt(const Vector3&, const Vector3&, const Vector3&);
};

typedef Matrix4 Mat4;
typedef Matrix4 mat4;

#endif // MATRIX4_H
