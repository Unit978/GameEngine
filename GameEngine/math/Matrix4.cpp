#include "Matrix4.h"
#include <cmath>
#include "MathUtil.h"

Matrix4::Matrix4()
{
    //ctor
}

Matrix4::Matrix4(const SquareMatrix<4>& other){
    for(unsigned row = 0; row < 4; row++)
        for(unsigned col = 0; col < 4; col++)
            elements[row][col] = other[row][col];
}

float Matrix4::determinant() const{
    float a, b, c, d, e, f, g, h, i, j, k, l, m, n, o ,p;
    a = elements[0][0];
    b = elements[0][1];
    c = elements[0][2];
    d = elements[0][3];

    e = elements[1][0];
    f = elements[1][1];
    g = elements[1][2];
    h = elements[1][3];

    i = elements[2][0];
    j = elements[2][1];
    k = elements[2][2];
    l = elements[2][3];

    m = elements[3][0];
    n = elements[3][1];
    o = elements[3][2];
    p = elements[3][3];

    return (a*f*k*p) - (a*f*l*o) - (a*g*j*p) + (a*g*l*n) + (a*h*j*o) - (a*h*k*n)
          -(b*e*k*p) + (b*e*l*o) + (b*g*i*p) - (b*g*l*m) - (b*h*i*o) + (b*h*k*m)
          +c*( (e*j*p) - (e*l*n) - (f*i*p)+ (f*l*m) + (h*i*n) - (h*j*m))
          +d*( (-e*j*o) + (e*k*n) + (f*i*o) - (f*k*m) - (g*i*n) + (g*j*m));
}


Matrix4 Matrix4::translation(const Vector3& v){
    Matrix4 tmp;
    tmp.setElement(0, 3, v.x);
    tmp.setElement(1, 3, v.y);
    tmp.setElement(2, 3, v.z);
    return tmp;
}

Matrix4 Matrix4::rotationRad(const Vector3& v){
    Matrix4 xRot, yRot, zRot;

    float cx = cosf(v.x);
    float sx = sinf(v.x);

    float cy = cosf(v.y);
    float sy = sinf(v.y);

    float cz = cosf(v.z);
    float sz = sinf(v.z);

    // Rotation about the x axis.
    xRot.setElement(1, 1, cx);
    xRot.setElement(1, 2, -sx);
    xRot.setElement(2, 1, sx);
    xRot.setElement(2, 2, cx);

    // Rotation about the y axis.
    yRot.setElement(0, 0, cy);
    yRot.setElement(0, 2, sy);
    yRot.setElement(2, 0, -sy);
    yRot.setElement(2, 2, cy);

    // Rotation about the z axis.
    zRot.setElement(0, 0, cz);
    zRot.setElement(0, 1, -sz);
    zRot.setElement(1, 0, sz);
    zRot.setElement(1, 1, cz);

    // Combine all the rotations.
    return zRot * yRot * xRot;
}

Matrix4 Matrix4::rotationDeg(const Vector3& v){
    Vector3 tmp = v;
    tmp.x = v.x * Deg2Rad;
    tmp.y = v.y * Deg2Rad;
    tmp.z = v.z * Deg2Rad;
    return rotationRad(tmp);
}

Matrix4 Matrix4::scale(const Vector3& v){
    Matrix4 tmp;
    tmp.setElement(0, 0, v.x);
    tmp.setElement(1, 1, v.y);
    tmp.setElement(2, 2, v.z);
    return tmp;
}

Matrix4 Matrix4::shear(const Vector3& v){
    Matrix4 tmp;
    tmp.setElement(0, 2, v.x);
    tmp.setElement(1, 1, v.y);
    tmp.setElement(2, 0, v.z);
    return tmp;
}

Matrix4 Matrix4::perspective(float fieldOfView, float aspectRatio, float zNear, float zFar){
    Matrix4 tmp;

    float t = tanf(fieldOfView/2);

    // Matrix elements that are important to the perspective matrix
    float m00, m11, m22, m23;

    m00 = 1 / (aspectRatio * t);
    m11 = 1 / t;
    m22 = (-zNear - zFar) / (zNear - zFar);
    m23 = (2 * zNear * zFar) / (zNear - zFar);

    tmp.setElement(0, 0, m00);
    tmp.setElement(1, 1, m11);
    tmp.setElement(2, 2, m22);
    tmp.setElement(2, 3, m23);

    tmp.setElement(3, 2, 1);
    tmp.setElement(3, 3, 0);

    return tmp;
}

Matrix4 Matrix4::lookAt(const Vector3& eye, const Vector3& target, const Vector3& up){

    // The direction from the eye to the target
    Vector3 n = (eye - target).normal();
    Vector3 s = n.cross(up.normal());
    Vector3 u = s.cross(n);

    Matrix4 tmp;

    // first row
    tmp.setElement(0, 0, s.x);
    tmp.setElement(0, 1, s.y);
    tmp.setElement(0, 2, s.z);

    // second row
    tmp.setElement(1, 0, u.x);
    tmp.setElement(1, 1, u.y);
    tmp.setElement(1, 2, u.z);

    // third row
    tmp.setElement(2, 0, n.x);
    tmp.setElement(2, 1, n.y);
    tmp.setElement(2, 2, n.z);

    return tmp;
}

Matrix4 Matrix4::ortho(float left, float right, float bottom, float top, float near, float far){

    Matrix4 tmp;

    float rightMinLeft = right - left;
    float topMinBottom = top - bottom;
    float farMinNear = far - near;

    tmp.setElement(0, 0, 2 / rightMinLeft);
    tmp.setElement(1, 1, 2 / topMinBottom);
    tmp.setElement(2, 2, -2 / farMinNear);

    tmp.setElement(0, 3, -(right + left) / rightMinLeft);
    tmp.setElement(1, 3, -(top + bottom) / topMinBottom);
    tmp.setElement(2, 3, -(far + near) / farMinNear);

    return tmp;
}
