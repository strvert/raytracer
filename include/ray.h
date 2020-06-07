#ifndef RAY_H
#define RAY_H

#include "vec.h"

struct Color;

class Ray
{
private:
    Vec<float> Orig;
    Vec<float> Dir;

public:
    Ray() {}
    Ray(const Vec<float>& Orig, const Vec<float>& Dir) : Orig(Orig), Dir(Dir) {}

    inline Vec<float> Origin() const { return Orig; }
    inline Vec<float> Direction() const { return Dir; }
    inline Vec<float> PointAtParameter(float t) const { return Orig + t*Dir; }
    Color ToScreenLerpColor(Color Col1, Color Col2) const;
};

#endif // RAY_H
