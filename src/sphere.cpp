#include "sphere.h"
#include "ray.h"

bool Sphere::Intersect(Ray& R)
{
    // 𝗍²(𝕕·𝕕)+2t{𝕕·(𝕒-𝕔)}+(𝕒-𝕔)·(𝕒-𝕔)-r² = 0
    // A = (𝕕·𝕕)
    // B = 2{𝕕·(𝕒-𝕔)}
    // C = (𝕒-𝕔)·(𝕒-𝕔)-r²

    Vec3f OC = R.Origin() - Center();
    float A = R.Direction().Dot(R.Direction());
    float B = 2.0 * R.Direction().Dot(OC);
    float C = OC.Dot(OC) - Radius() * Radius();

    return (B*B - 4.0*A*C) > 0;
}
