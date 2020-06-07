#ifndef METAL_MATERIAL_H
#define METAL_MATERIAL_H

#include "mats/material.h"
#include "color.h"


class Ray;
struct HitRecord;

template<typename T>
class Vec;

class Metal : public Material
{
private:
    Vec<float> Refrect(const Vec<float>& V, const Vec<float>& N);

public:
    Color Albedo;
    float Rough;

    Metal(const Color& A, const float R) : Albedo(A), Rough(R) {}
    virtual ~Metal() {}

    virtual bool Scatter(const Ray& RIn, const HitRecord& Rec, Color& Attenuation, Ray& Scattered) const override;
};

#endif // METAL_MATERIAL_H

