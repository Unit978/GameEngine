#ifndef VECTOR2_H
#define VECTOR2_H

#include "Vector.h"
#include "Vector3.h"

/**
    A 2D float vector whose "z" value is conceptually 0.
*/

class Vector2 : public Vector<2>
{
public:
    Vector2();
    Vector2(float x, float y);
    Vector2(const Vector&);
    Vector2(const Vector<3>&);
    Vector2(const Vector<4>&);

    // Obtain the normalized orthogonal vector.
    Vector2 orthogonal() const;

    // Direction is the angle between the X axis and the vector.
    void setDirection(float value);

    // Uses the angle between i-unit vector and the vector itself.
    float direction() const;

    // To handle the reference value assignments.
    Vector2& operator=(const Vector2&);

    // References to the individual components of the array.
    float& x;
    float& y;
};

typedef Vector2 Vec2;
typedef Vector2 vec2;

#endif // VECTOR2_H
