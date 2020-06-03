#include "sphere.h"
#include "ray.h"
#include <cmath>
#include <iostream>

bool Sphere::Hit(const Ray& R, float TMin, float TMax, HitRecord& Rec) const
{
    // A = (𝕕·𝕕)
    // B = 𝕕·(𝕒-𝕔)
    // C = (𝕒-𝕔)·(𝕒-𝕔)-r²

    Vec3f OC = R.Origin() - Center();
    float A = R.Direction().Dot(R.Direction());
    float B = R.Direction().Dot(OC);
    float C = OC.Dot(OC) - Radius() * Radius();
    float D = (B*B - A*C);

    if (D > 0)
    {
        float T = (-B - std::sqrt(D)) / A;
        if (T < TMax && T > TMin)
        {
            Rec.T = T;
            Rec.P = R.PointAtParameter(T);
            Rec.N = (Rec.P - Center()) / Radius();
            return true;
        }
        T = (-B + std::sqrt(D)) / A;
        if (T < TMax && T > TMin)
        {
            Rec.T = T;
            Rec.P = R.PointAtParameter(T);
            Rec.N = (Rec.P - Center()) / Radius();
            return true;
        }
    }
    return false;
}
