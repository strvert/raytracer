#ifndef LAMBERTIAN_MATERIAL_H
#define LAMBERTIAN_MATERIAL_H

#include "mats/material.h"
#include "color.h"

struct Color;
struct HitRecord;

class Lambertian : public Material
{
public:
    Color Albedo;

    Lambertian(const Color& A) : Albedo(A) {}
    virtual ~Lambertian() {}

    virtual bool Scatter(const Ray& RIn, const HitRecord& Rec, Color& Attenuation, Ray& Scattered) const override;
};

#endif // LAMBERTIAN_MATERIAL_H

