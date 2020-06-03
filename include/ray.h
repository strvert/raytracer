#ifndef RAY_H
#define RAY_H

#include "vec3.h"
#include "color.h"

class Ray
{
private:
    Vec3f Orig;
    Vec3f Dir;

public:
    Ray() {}
    Ray(const Vec3f& Orig, const Vec3f& Dir) : Orig(Orig), Dir(Dir) {}

    inline Vec3f Origin() const { return Orig; }
    inline Vec3f Direction() const { return Dir; }
    inline Vec3f PointAtParameter(float t) const { return Orig + t*Dir; }
    Color ToScreenLerpColor(Color Col1, Color Col2) const;
};

#endif // RAY_H
