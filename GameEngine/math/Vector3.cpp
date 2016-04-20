#include "Vector3.h"

Vector3::Vector3() :
    x(components[0]), y(components[1]), z(components[2])
{
    //ctor
}

Vector3::Vector3(float x, float y, float z) :
    x(components[0]), y(components[1]), z(components[2])
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3::Vector3(const Vector& v) :
    x(components[0]), y(components[1]), z(components[2])
{
    x = v[0];
    y = v[1];
    z = v[2];
}

Vector3::Vector3(const Vector<4>& v) :
    x(components[0]), y(components[1]), z(components[2])
{
    x = v[0];
    y = v[1];
    z = v[2];
}

Vector3 Vector3::cross(const Vector3& v) const{
    float xn = (y * v.z) - (z * v.y);
    float yn = (z * v.x) - (x * v.z);
    float zn = (x * v.y) - (y * v.x);
    return Vector3(xn, yn, zn);
}

Vector3& Vector3::operator=(const Vector3& v){
    if(this != &v){
        x = v.x;
        y = v.y;
        z = v.z;
    }
    return *this;
}
