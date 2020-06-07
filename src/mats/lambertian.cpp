#include "mats/lambertian.h"
#include "hitable.h"
#include "utils.h"
#include "ray.h"

bool Lambertian::Scatter(const Ray& RIn, const HitRecord& Rec, Color& Attenuation, Ray& Scattered) const
{
    Vec<float> Target = Rec.P + Rec.N + Utils::RandInUnitSphere();
    Scattered = Ray(Rec.P, Target-Rec.P);
    Attenuation = Albedo;
    return true;
}
