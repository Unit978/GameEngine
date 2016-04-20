#include "Vector.h"
#include <cmath>

template <unsigned size>
Vector<size>::Vector()
{}

template <unsigned size>
Vector<size>::~Vector()
{}

template <unsigned size>
Vector<size> Vector<size>::add(const Vector& v) const{

    Vector u;
    for(unsigned i = 0; i < size; i++)
        u.components[i] = components[i] + v[i];

    return u;
}

template <unsigned size>
Vector<size> Vector<size>::sub(const Vector& v) const{

    Vector u;
    for(unsigned i = 0; i < size; i++)
        u.components[i] = components[i] - v[i];

    return u;
}

template <unsigned size>
void Vector<size>::scale(float scale){
    for (float& f : components)
        f *= scale;
}

template <unsigned size>
float Vector<size>::dot(const Vector& v) const{
    float sum = 0;
    for(unsigned i = 0; i < size; i++){
        sum += components[i] * v[i];
    }
    return sum;
}

template <unsigned size>
float Vector<size>::angle(const Vector& v) const{
    float numer = this->dot(v);
    float denom = magnitude() * v.magnitude();
    return acos(numer / denom);
}

template <unsigned size>
Vector<size> Vector<size>::normal() const{

    Vector norm;
    float mag = magnitude();

    for(unsigned i = 0; i < size; i++)
        norm[i] = components[i] / mag;

    return norm;
}

template <unsigned size>
void Vector<size>::normalize(){
    float mag = magnitude();
    for (float& f : components)
        f /= mag;
}

template <unsigned size>
void Vector<size>::zero(){
    for(float& f : components)
        f = 0;
}

template <unsigned size>
bool Vector<size>::isZero() const{
    for (const float f : components)
        if (f != 0) return false;
    return true;
}

template <unsigned size>
void Vector<size>::setMagnitude(float mag){

    // Use properties of similar triangles.
    float m = magnitude();
    if(m != 0){
        float ratio = mag / m;

        for (float& f : components)
            f *= ratio;
    }
}

template <unsigned size>
float Vector<size>::magnitude() const{
    return sqrtf(sqMagnitude());
}

template <unsigned size>
float Vector<size>::sqMagnitude() const{
    float sum = 0;
    for(const float f : components)
        sum += f * f;
    return sum;
}

template <unsigned size>
bool Vector<size>::operator==(const Vector& v) const{

    for(unsigned i = 0; i < size; i++)
        if (components[i] != v[i]) return false;

    return true;
}

template <unsigned size>
bool Vector<size>::operator!=(const Vector& v) const{
    return !(*this==v);
}

template <unsigned size>
const Vector<size>& Vector<size>::operator=(const Vector& v){
    if(this != &v){
        for(unsigned i = 0; i < size; i++)
            components[i] = v[i];
    }
    return *this;
}

template <unsigned size>
Vector<size> Vector<size>::operator+(const Vector& v) const{
    return add(v);
}

template <unsigned size>
Vector<size> Vector<size>::operator-(const Vector& v) const{
    return sub(v);
}

template <unsigned size>
Vector<size> Vector<size>::operator*(float scale) const{
    Vector tmp;
    for(unsigned i = 0; i < size; i++)
        tmp[i] = components[i] * scale;

    return tmp;
}

template <unsigned size>
const Vector<size>& Vector<size>::operator+=(const Vector& v){

    for(unsigned i = 0; i < size; i++)
        components[i] += v[i];

    return *this;
}

template <unsigned size>
const Vector<size>& Vector<size>::operator-=(const Vector& v){
    for(unsigned i = 0; i < size; i++)
        components[i] -= v[i];
    return *this;
}

template <unsigned size>
const Vector<size>& Vector<size>::operator*=(float scale){
    this->scale(scale);
    return *this;
}

template<unsigned size>
float Vector<size>::operator[](int index) const{
    return components[index];
}

template<unsigned size>
float& Vector<size>::operator[](int index){
    return components[index];
}

template class Vector<2>;
template class Vector<3>;
template class Vector<4>;
