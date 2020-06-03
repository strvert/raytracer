#ifndef SPHERE_H
#define SPHERE_H

#include "vec3.h"

class Ray;

class Sphere
{
private:
    Vec3f Cntr;
    float Rds;

public:
    Sphere(Vec3f Center, float Radius): Cntr(Center), Rds(Radius) {}
    Sphere(Vec3f Center): Cntr(Center), Rds(0.5) {}

    inline Vec3f Center() { return Cntr; };
    inline float Radius() { return Rds; };
    bool Intersect(Ray& R);
};

#endif // SPHERE_H
