#include "ray.h"

Color Ray::ToScreenLerpColor(Color Col)
{
    Vec3f UnitDir = Dir.Normalize();
    float T = 0.5 * (UnitDir.Y() + 1.0);
    return ((1.0 - T)*Vec3f(1.0, 1.0, 1.0) + T*Vec3f(Col.X() / 255.0, Col.Y() / 255.0, Col.Z() / 255.0))*255.0;
}
