#ifndef SPHERE_H
#define SPHERE_H

#include "vec3.h"
#include "color.h"
#include "hitable.h"

class Ray;

class Sphere: public Hitable
{
private:
    Vec3f Cntr;
    float Rds;

public:
    Sphere(Vec3f Center, float Radius): Cntr(Center), Rds(Radius) {}
    Sphere(Vec3f Center): Cntr(Center), Rds(0.5) {}
    virtual ~Sphere() {}

    inline Vec3f Center() const { return Cntr; };
    inline float Radius() const { return Rds; };

    virtual bool Hit(const Ray& R, float TMin, float TMax, HitRecord& Rec) const override;
};

#endif // SPHERE_H
