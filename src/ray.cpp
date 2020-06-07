#include "ray.h"

Color Ray::ToScreenLerpColor(Color Col1, Color Col2) const
{
    Vec<float> UnitDir = Dir.Normalize();
    float T = 0.5 * (UnitDir.Y() + 1.0);
    return (1.0 - T) * Col1 + T*Col2;
}
