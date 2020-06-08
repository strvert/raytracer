#include "mats/dielectric.h"
#include "color.h"
#include "vec.h"
#include "ray.h"
#include "hitable.h"
#include "utils.h"

bool Dielectric::Scatter(const Ray& RIn, const HitRecord& Rec, Color& Attenuation, Ray& Scattered) const
{
    Vec<float> OutwardNormal;
    float NiOverNt;
    Attenuation = Color::FromRGBA256(255, 255, 255);
    Vec<float> Refracted;
    float ReflectProb;
    float Cosine;

    Vec<float> Reflected = Utils::Reflect(RIn.Direction(), Rec.N);

    if (RIn.Direction().Dot(Rec.N) > 0)
    {
        OutwardNormal = -Rec.N;
        NiOverNt = RefIdx;
        Cosine = RefIdx * RIn.Direction().Dot(Rec.N) / RIn.Direction().Length();
    }
    else
    {
        OutwardNormal = Rec.N;
        NiOverNt = 1.000292 / RefIdx;
        Cosine = -RIn.Direction().Dot(Rec.N) / RIn.Direction().Length();
    }

    if (Utils::Refract(RIn.Direction(), OutwardNormal, NiOverNt, Refracted))
    {
        ReflectProb = Utils::Schlink(Cosine, RefIdx);
    }
    else
    {
        ReflectProb = 1.0;
        Scattered = Ray(Rec.P, Reflected);
    }

    if (Utils::RandZeroToOne() < ReflectProb)
    {
        Scattered = Ray(Rec.P, Reflected);
    }
    else
    {
        Scattered = Ray(Rec.P, Refracted);
    }

    return true;
}
