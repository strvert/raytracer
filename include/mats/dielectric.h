#ifndef DIELECTRIC_MATERIAL_H
#define DIELECTRIC_MATERIAL_H

#include "mats/material.h"

class Dielectric : public Material
{
private:
    float RefIdx; // refractive index
public:

    Dielectric(const float R) : RefIdx(R) {}
    virtual ~Dielectric() {}

    virtual bool Scatter(const Ray& RIn, const HitRecord& Rec, Color& Attenuation, Ray& Scattered) const override;
};

#endif // DIELECTRIC_MATERIAL_H

