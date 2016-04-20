#ifndef VECTOR_H
#define VECTOR_H

#include <ostream>

using std::ostream;

/**
    A general mathematical vector.
*/

// Template is used to be able to create a fixed sized array
// upon compile time to avoid using the heap.
template<unsigned size>
class Vector {

friend ostream& operator<<(ostream& os, const Vector& v){
    os << '<';
    unsigned i = 0;
    for(const float f : v.components){
        os << f;

        // Add a space if it's not the last component.
        if (++i < size) os << ", ";
    }
    return os << '>';
}

public:
    Vector();
    ~Vector();

    Vector add(const Vector&) const;
    Vector sub(const Vector&) const;

    // Scalar multiplication.
    void scale(float scale);

    // Dot product.
    float dot(const Vector&) const;

    // Angle between two vectors.
    float angle(const Vector&) const;

    // Vector normalization.
    Vector normal() const;
    void normalize();

    // Zero out the x and y components
    void zero();
    bool isZero() const;

    void setMagnitude(float);
    float magnitude() const;
    float sqMagnitude() const;

    bool operator==(const Vector&) const;
    bool operator!=(const Vector&) const;
    const Vector& operator=(const Vector&);

    Vector operator+(const Vector&) const;
    Vector operator-(const Vector&) const;
    Vector operator*(float scale) const;

    const Vector& operator+=(const Vector&);
    const Vector& operator-=(const Vector&);
    const Vector& operator*=(float scale);

    // Indexing to access vector elements
    float operator[](int index) const;
    float& operator[](int index);

    float components[size];
};

#endif // VECTOR_H
