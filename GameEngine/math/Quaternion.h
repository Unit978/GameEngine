/*
    This quaternion class is used for rotations around an axis in 3D.
    The W component is the angle of rotation about some axis "A".
    Where "A" is a vector with the components X, Y, Z.
*/

#ifndef QUATERNION_H
#define QUATERNION_H

#include "Vector3.h"
#include "Matrix4.h"
#include "../util/MeasurementUnits.h"

#include <ostream>

using std::ostream;

class Quaternion{

friend ostream& operator<<(ostream& os, const Quaternion&);

public:

    // The default values represent the initial state of a quaternion, no rotation.
    Quaternion(float=1, float=0, float=0, float=0);

    // Create a quaternion from the initial angle (radians) and axis;
    Quaternion(const Radians& rad, const Vector3& axis);
    Quaternion(const Degrees& deg, const Vector3& axis);

    // Set the quaternion to its identity form.
    void identity();

    // Make the quaternion into a unit quaternion.
    // Unit quaternions describe a 4-dimensional sphere (hyper sphere), and all
    // of the quaternion's end points lay in hyper sphere. Because of this,
    // multiplying two unit quaternions results in a third unit quaternion.
    void normalize();
    float magnitude() const;

    // The squared magnitude of the quaternion
    float sqMagnitude() const;
    void conjugate();

    Quaternion getConjugate() const;

    // This rotates the quaternion by the specified angle about the Vector3 axis in space.
    void rotate(const Radians& rad, const Vector3& axis);
    void rotate(const Degrees& deg, const Vector3& axis);

    // Convert the quaternion to its matrix form.
    // Assuming that the the quaternion is normalized.
    Matrix4 toMatrix() const;

    Vector3 toVector() const;

    // Take in the Euler angles and modify the quaternion to fit the rotation.
    // Order of rotation: yaw (y), pitch (x), roll (z)
    void setEulerAngles(const Radians& yaw, const Radians& pitch, const Radians& roll);
    void setEulerAngles(const Degrees& yaw, const Degrees& pitch, const Degrees& roll);

    // Takes in the 3 axis rotations as a Vector3.
    void setEulerAnglesRad(const Vector3& angles);
    void setEulerAnglesDeg(const Vector3& angles);
/*
    // Returns the rotations of each x, y, z axis, as a Vector3, represented
    // by the quaternion itself.
    Vector3 getEulerAngles() const;
    int getGimbalPole() const;
*/

    // Obtain directional vectors relative to the quaternion rotation.
    Vector3 getForward() const;
    Vector3 getBack() const;
    Vector3 getUp() const;
    Vector3 getDown() const;
    Vector3 getRight() const;
    Vector3 getLeft() const;

    // Quaternion comparisons
    bool operator==(const Quaternion&) const;
    bool operator!=(const Quaternion&) const;

    // Quaternion multiplication, NOT commutative
    Quaternion operator*(const Quaternion&) const;

    Quaternion operator*(const Vector3&) const;

    // Quaternion addition
    Quaternion operator+(const Quaternion&) const;
    const Quaternion& operator*=(const Quaternion&);
    const Quaternion& operator+=(const Quaternion&);

    // Rotate the Vector v by the angle specified about the axis and return the new rotated vector
    static Vector3 rotate(const Radians& rad, const Vector3& v, const Vector3& axis);
    static Vector3 rotate(const Degrees& deg, const Vector3& v, const Vector3& axis);

    // Rotate the vector about the quaternion by interpreting the vector as a unit quaternion
    static Vector3 rotate(const Vector3&, const Quaternion&);

//private:
    float w, x, y, z;
};

#endif // QUATERNION_H
