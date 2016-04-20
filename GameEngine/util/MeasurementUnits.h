#ifndef MEASUREMENTUNITS_H
#define MEASUREMENTUNITS_H

#include <ostream>
#include "../math/MathUtil.h"

using std::ostream;

// A unit in the MKS system
template<int M, int K, int S> struct Unit {
    enum { m = M, kg = K, s = S };
};

// A magnitude with a unit
template<typename Unit>
struct Value {

    // Magnitude
    float value;

    // construct a Value from a long double
    explicit constexpr Value(long double d) : value(d) {}

    friend ostream& operator<<(ostream& os, const Value& v){
        return os << v.value;
    }
};

using Distance = Unit<1, 0, 0>;

// meters/second type
using Speed = Value<Unit<1, 0, -1>>;

// meters/second/second type
using Acceleration = Value<Unit<1, 0, -2>>;

// unit: second
using Second = Unit<0, 0, 1>;

// unit: second*second
using Second2 = Unit<0, 0, 2>;


constexpr Value<Distance> operator"" _m(long double d){
    return Value<Distance>(d);
}

// A f-p literal suffixed by ‘s’
constexpr Value<Second> operator "" _s(long double d){
    return Value<Second>(d);
}

// a f-p literal  suffixed by ‘s2’
constexpr Value<Second2> operator"" _s2(long double d){
    return Value<Second2>(d);
}

constexpr Speed operator/(Value<Distance> d, Value<Second> s){
    return Speed(d.value / s.value);
}

// Forward declaration of Radians so Degrees can use it.
struct Radians;

struct Degrees{

public:
    explicit constexpr Degrees(float value) : value(value) {}
    explicit Degrees(const Radians&); // Convert radians to degrees via CTOR

    float operator+(float f) const { return value + f; }
    float operator-(float f) const { return value - f; }
    float operator*(float f) const { return value * f; }
    float operator/(float f) const { return value / f; }

    const Degrees& operator+=(float f){ value += f; return *this; }
    const Degrees& operator-=(float f){ value -= f; return *this; }
    const Degrees& operator*=(float f){ value *= f; return *this; }
    const Degrees& operator/=(float f){ value /= f; return *this; }

    float value;
};

constexpr Degrees operator"" _deg(long double value){
    return Degrees(value);
}

struct Radians{

public:
    explicit constexpr Radians(float value) : value(value) {}
    explicit Radians(const Degrees&); // Convert degrees to radians via CTOR

    float operator+(float f) const { return value + f; }
    float operator-(float f) const { return value - f; }
    float operator*(float f) const { return value * f; }
    float operator/(float f) const { return value / f; }

    const Radians& operator+=(float f){ value += f; return *this; }
    const Radians& operator-=(float f){ value -= f; return *this; }
    const Radians& operator*=(float f){ value *= f; return *this; }
    const Radians& operator/=(float f){ value /= f; return *this; }

    float value;
};

constexpr Radians operator"" _rad(long double value){
    return Radians(value);
}

#endif // MEASUREMENTUNITS_H




