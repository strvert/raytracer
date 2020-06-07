#ifndef SPHERE_H
#define SPHERE_H
#include <memory>

#include "vec.h"
#include "hitable.h"
#include "mats/material.h"

class Ray;

class Sphere: public Hitable
{
private:
    Vec<float> Cntr;
    float Rds;
    std::shared_ptr<Material> Mat;

public:

    Sphere(Vec<float> Center, float Radius, std::shared_ptr<Material> Mat): Cntr(Center), Rds(Radius), Mat(Mat) {}
    Sphere(Vec<float> Center, std::shared_ptr<Material> Mat): Cntr(Center), Rds(0.5), Mat(Mat) {}
    virtual ~Sphere() {}

    inline Vec<float> Center() const { return Cntr; };
    inline float Radius() const { return Rds; };

    virtual bool Hit(const Ray& R, float TMin, float TMax, HitRecord& Rec) const override;
};

#endif // SPHERE_H
