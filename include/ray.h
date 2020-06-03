#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray
{
private:
    Vec3f Orig;
    Vec3f Dir;

public:
    Ray() {}
    Ray(const Vec3f& Orig, const Vec3f& Dir) : Orig(Orig), Dir(Dir) {}
    Vec3f Origin() const { return Orig; }
    Vec3f Direction() const { return Dir; }
    Vec3f PointAtParameter(float t) const { return Orig + t*Dir; }
    Color ToScreenLerpColor(Color Col);
};

#endif // RAY_H
