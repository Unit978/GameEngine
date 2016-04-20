#include "MeasurementUnits.h"

Degrees::Degrees(const Radians& r) :
    value (r.value * Rad2Deg)
{

}

Radians::Radians(const Degrees& d) :
    value(d.value * Deg2Rad)
{

}
