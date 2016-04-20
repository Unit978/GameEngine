#include "Vector4.h"

Vector4::Vector4() :
    x(components[0]), y(components[1]), z(components[2]), w(components[3])
{
}

Vector4::Vector4(float x, float y, float z, float w) :
    x(components[0]), y(components[1]), z(components[2]), w(components[3])
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

Vector4& Vector4::operator=(const Vector4& v){
    if(this != &v){
        x = v.x;
        y = v.y;
        z = v.z;
        w = v.w;
    }
    return *this;
}
