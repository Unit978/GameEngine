#ifndef VECTOR3_H
#define VECTOR3_H

#include "Vector.h"
#include "Vector4.h"

class Vector3 : public Vector<3> {

public:
    Vector3();
    Vector3(float x, float y, float z);
    Vector3(const Vector&);
    Vector3(const Vector<4>&);

    Vector3 cross(const Vector3& vec) const;

    // To handle the reference value assignments.
    Vector3& operator=(const Vector3&);

    // References to the individual components of the array.
    float& x;
    float& y;
    float& z;
};

typedef Vector3 Vec3;
typedef Vector3 vec3;

#endif // VECTOR3_H
