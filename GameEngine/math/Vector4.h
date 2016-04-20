#ifndef VECTOR4_H
#define VECTOR4_H

#include "Vector.h"

class Vector4 : public Vector<4>
{
public:
    Vector4();
    Vector4(float x, float y, float z, float w);

    // To handle the reference value assignments.
    Vector4& operator=(const Vector4&);

    // References to the individual components of the array.
    float& x;
    float& y;
    float& z;
    float& w;
};

typedef Vector4 Vec4;
typedef Vector4 vec4;

#endif // VECTOR4_H
