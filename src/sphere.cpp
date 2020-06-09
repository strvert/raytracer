#include "sphere.h"
#include "ray.h"
#include <cmath>
#include <iostream>

bool Sphere::Hit(const Ray& R, float TMin, float TMax, HitRecord& Rec) const
{
    // A = (𝕕·𝕕)
    // B = 𝕕·(𝕒-𝕔)
    // C = (𝕒-𝕔)·(𝕒-𝕔)-r²

    Vec<float> OC = R.Origin() - Center();
    float A = R.Direction().SquaredLength();
    float B = R.Direction().Dot(OC);
    float C = OC.Dot(OC) - Radius() * Radius();
    float D = (B*B - A*C);

    Vec<float> Dn = R.Direction().Normalize();
    float E = ((Dn.Dot(-OC))*Dn+OC).Length();


    if (E < std::abs(Radius()))
    {
        float T = (-B - std::sqrt(D)) / A;
        if (T < TMax && T > TMin)
        {
            Rec.T = T;
            Rec.P = R.PointAtParameter(T);
            Rec.N = (Rec.P - Center()) / Radius();
            Rec.Mat = Mat;
            return true;
        }
        T = (-B + std::sqrt(D)) / A;
        if (T < TMax && T > TMin)
        {
            Rec.T = T;
            Rec.P = R.PointAtParameter(T);
            Rec.N = (Rec.P - Center()) / Radius();
            Rec.Mat = Mat;
            return true;
        }
    }
    return false;
}
