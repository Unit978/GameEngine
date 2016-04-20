#include "Vector2.h"
#include <cmath>

Vector2::Vector2() :
    x(components[0]), y(components[1])
{
    //ctor
}

Vector2::Vector2(float x, float y) :
    x(components[0]), y(components[1])
{
    this->x = x;
    this->y = y;
}

Vector2::Vector2(const Vector& v) :
    x(components[0]), y(components[1])
{
    x = v[0];
    y = v[1];
}

Vector2::Vector2(const Vector<3>& v) :
    x(components[0]), y(components[1])
{
    x = v[0];
    y = v[1];
}

Vector2::Vector2(const Vector<4>& v) :
    x(components[0]), y(components[1])
{
    x = v[0];
    y = v[1];
}

Vector2 Vector2::orthogonal() const{
    Vector2 tmp = Vector2(y, -x);
    tmp.normalize();
    return tmp;
}

void Vector2::setDirection(float value){
    float m = magnitude();
    x = m * cos(value);
    y = m * sin(value);
}

float Vector2::direction() const{
    float r = acos(x / magnitude());
    if(y < 0) r *= -1;
    return r;
}

Vector2& Vector2::operator=(const Vector2& v){
    if(this != &v){
        x = v.x;
        y = v.y;
    }
    return *this;
}



