#include "mats/metallic.h"
#include "utils.h"
#include "ray.h"
#include "hitable.h"

bool Metal::Scatter(const Ray& RIn, const HitRecord& Rec, Color& Attenuation, Ray& Scattered) const
{
    Vec<float> Reflected = Utils::Refrect(RIn.Direction().Normalize(), Rec.N);
    if (Rough == 0)
    {
        Scattered = Ray(Rec.P, Reflected);
    }
    else
    {
        Scattered = Ray(Rec.P, Reflected + Rough*Utils::RandInUnitSphere());
    }
    Attenuation = Albedo;
    return Scattered.Direction().Dot(Rec.N) > 0;
}
