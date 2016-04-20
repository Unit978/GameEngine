#include "Quaternion.h"

#include <cmath>
#include "MathUtil.h"

Quaternion::Quaternion(float w, float x, float y, float z) : w(w), x(x), y(y), z(z){}

Quaternion::Quaternion(const Radians& rad, const Vector3& axis){
    float c = cosf(rad/2);
    float s = sinf(rad/2);
    w = c;
    x = axis.x * s;
    y = axis.y * s;
    z = axis.z * s;
}

Quaternion::Quaternion(const Degrees& deg, const Vector3& axis){

    float rad = (deg * Deg2Rad) / 2;
    float c = cosf(rad);
    float s = sinf(rad);
    w = c;
    x = axis.x * s;
    y = axis.y * s;
    z = axis.z * s;
}

void Quaternion::identity(){
    w = 1;
    x = y = z = 0;
}

void Quaternion::normalize(){
    float mag = this->magnitude();
    w /= mag;
    x /= mag;
    y /= mag;
    z /= mag;
}

float Quaternion::magnitude() const{
    return sqrtf(w*w + x*x + y*y + z*z);
}

float Quaternion::sqMagnitude() const{
    return w*w + x*x + y*y + z*z;
}

void Quaternion::conjugate(){
    x *= -1;
    y *= -1;
    z *= -1;
}

Quaternion Quaternion::getConjugate() const{
    return Quaternion(w, -x, -y, -z);
}

void Quaternion::rotate(const Radians& rad, const Vector3& axis){

    float a = rad.value;

    // keep the angle in between -2*pi : 2*pi
    if (a < 0 || a > PI2)
        a = fmod(a, PI2);

    // This represents the change in rotation
    Quaternion localRotation(Radians(a), axis);
    localRotation.normalize();

    // Rotate the quaternion by the local rotation.
    *this = localRotation * (*this);

    // check for floating point inaccuracy and keep the quaternion normalized
    if (fabs( 1 - sqMagnitude()) > 0.0001 )
        normalize();
}

void Quaternion::rotate(const Degrees& deg, const Vector3& axis){
    rotate(Radians(deg) , axis);
}

Matrix4 Quaternion::toMatrix() const{
    Matrix4 tmp;

    // values for the top left 3x3 sub matrix
    float a, b, c, d, e, f, g, h, i;

    float x2 = x*x;
    float y2 = y*y;
    float z2 = z*z;

    a = 1 - (2*y2) - (2*z2);
    b = (2*x*y) - (2*w*z);
    c = (2*x*z) + (2*w*y);

    d = (2*x*y) + (2*w*z);
    e = 1 - (2*x2) - (2*z2);
    f = (2*y*z) - (2*w*x);  // switched to - from +

    g = (2*x*z) - (2*w*y);
    h = (2*y*z) + (2*w*x);  // switched to + from -
    i = 1 - (2*x2) - (2*y2);

    tmp.setElement(0, 0, a);
    tmp.setElement(0, 1, b);
    tmp.setElement(0, 2, c);

    tmp.setElement(1, 0, d);
    tmp.setElement(1, 1, e);
    tmp.setElement(1, 2, f);

    tmp.setElement(2, 0, g);
    tmp.setElement(2, 1, h);
    tmp.setElement(2, 2, i);

    return tmp;
}

Vector3 Quaternion::toVector() const{
    return Vector3(x, y, z);
}

// Order of rotation: yaw (y), pitch (x), roll (z)
void Quaternion::setEulerAngles(const Radians& yaw, const Radians& pitch, const Radians& roll){

    Quaternion qroll ( Radians(cosf(yaw/2)),   Vector3(0, -sinf(yaw/2), 0)   );
    Quaternion qpitch( Radians(cosf(pitch/2)), Vector3(-sinf(pitch/2), 0, 0) );
    Quaternion qyaw  ( Radians(cosf(roll/2)),  Vector3(0, 0, -sinf(roll/2))  );

    // Combine all rotations
    *this = qroll * qpitch * qyaw;
}

// Order of rotation: yaw (y), pitch (x), roll (z)
void Quaternion::setEulerAngles(const Degrees& yaw, const Degrees& pitch, const Degrees& roll){
    setEulerAngles(Radians(yaw), Radians(pitch), Radians(roll));
}

// Order of rotation: yaw (y), pitch (x), roll (z)
void Quaternion::setEulerAnglesRad(const Vector3& angles){
    setEulerAngles(Radians(angles.y), Radians(angles.x), Radians(angles.z));
}

// Order of rotation: yaw (y), pitch (x), roll (z)
void Quaternion::setEulerAnglesDeg(const Vector3& angles){
    float yrad = angles.y * Deg2Rad;
    float xrad = angles.x * Deg2Rad;
    float zrad = angles.z * Deg2Rad;
    setEulerAngles(Radians(yrad), Radians(xrad), Radians(zrad));
}
/*
Vector3 Quaternion::getEulerAngles() const{
    Vector3 tmp;

    return tmp;
}

int Quaternion::getGimbalPole() const{
    return 0;
}
*/
Vector3 Quaternion::getForward() const{
    return Quaternion::rotate(Vector3(0, 0, 1), *this);
}

Vector3 Quaternion::getBack() const{
    return Quaternion::rotate(Vector3(0, 0, -1), *this);
}

Vector3 Quaternion::getUp() const{
    return Quaternion::rotate(Vector3(0, 1, 0), *this);
}

Vector3 Quaternion::getDown() const{
    return Quaternion::rotate(Vector3(0, -1, 0), *this);
}

Vector3 Quaternion::getRight() const{
    return Quaternion::rotate(Vector3(1, 0, 0), *this);
}

Vector3 Quaternion::getLeft() const{
    return Quaternion::rotate(Vector3(-1, 0, 0), *this);
}

bool Quaternion::operator==(const Quaternion& q) const{
    return w == q.w && x == q.x && y == q.y && z == q.z;
}

bool Quaternion::operator!=(const Quaternion& q) const{
    return !(*this == q);
}

Quaternion Quaternion::operator*(const Quaternion& q) const{
    Quaternion tmp;
    tmp.w = w*q.w - x*q.x - y*q.y - z*q.z;
    tmp.x = w*q.x + x*q.w + y*q.z - z*q.y;
    tmp.y = w*q.y - x*q.z + y*q.w + z*q.x;
    tmp.z = w*q.z + x*q.y - y*q.x + z*q.w;
    return tmp;
}

Quaternion Quaternion::operator*(const Vector3& v) const{
    Quaternion tmp(1, v.x, v.y, v.z);
    tmp.normalize();
    return (*this) * tmp;
}


Quaternion Quaternion::operator+(const Quaternion& q) const{
    Quaternion tmp;
    tmp.w = w + q.w;
    tmp.x = x + q.x;
    tmp.y = y + q.y;
    tmp.z = z + q.z;
    return tmp;
}

const Quaternion& Quaternion::operator*=(const Quaternion& q){
    w = w*q.w - x*q.x - y*q.y - z*q.z;
    x = w*q.x + x*q.w + y*q.z - z*q.y;
    y = w*q.y - x*q.z + y*q.w + z*q.x;
    z = w*q.z + x*q.y - y*q.x + z*q.w;
    return *this;
}

const Quaternion& Quaternion::operator+=(const Quaternion& q){
    w += q.w;
    x += q.x;
    y += q.y;
    z += q.z;
    return *this;
}

Vector3 Quaternion::rotate(const Radians& rad, const Vector3& v, const Vector3& axis){
    float c = cosf(rad/2);
    float s = sinf(rad/2);

    Quaternion qaxis(Radians(c), axis*s);
    Quaternion qvector(Radians(1), v);

    qaxis.normalize();
    qvector.normalize();

    Quaternion qresult = qaxis * qvector * qaxis.getConjugate();
    return qresult.toVector();
}

Vector3 Quaternion::rotate(const Degrees& deg, const Vector3& v, const Vector3& axis){
    return rotate(Radians(deg), v, axis);
}

Vector3 Quaternion::rotate(const Vector3& v, const Quaternion& q){
    Quaternion result = q * v * q.getConjugate();
    return result.toVector().normal();
}

ostream& operator<<(ostream& os, const Quaternion& q){
    return os << "q: " << q.w << ", <" << q.x << ", " << q.y << ", " << q.z << ">";
}
