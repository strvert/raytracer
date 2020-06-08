#include "utils.h"

#include <random>
#include "vec.h"

auto Utils::Mt = []{
    std::random_device Rnd;
    return std::mt19937(Rnd());
}();
auto Utils::RZeroToOne = std::uniform_real_distribution<double>(0.0, 1.0);
auto Utils::RMinusOneToPlusOne = std::uniform_real_distribution<double>(-1.0, 1.0);

Vec<float> Utils::RandInUnitSphere()
{
    Vec<float> P;
    do {
        P = Vec<float>(RandMinusOneToPlusOne(), RandMinusOneToPlusOne(), RandMinusOneToPlusOne());
    } while (P.SquaredLength() >= 1.0);
    return P;
}

Vec<float> Utils::Reflect(const Vec<float>& V, const Vec<float>& N)
{
    return V - 2*V.Dot(N)*N;
}

bool Utils::Refract(const Vec<float>& V, const Vec<float>& N, float NiOverNt, Vec<float>& Refracted)
{
    Vec<float> UnitVec = V.Normalize();
    float Dt = UnitVec.Dot(N);
    float D = 1.0 - NiOverNt*NiOverNt*(1 - Dt*Dt);
    if (D > 0)
    {
        Refracted = NiOverNt*(UnitVec - N*Dt) - N*std::sqrt(D);
        return true;
    }
    else
    {
        return false;
    }
}

float Utils::Schlink(const float Cosine, const float RefIdx)
{
    float R0 = (1-RefIdx) / (1+RefIdx);
    R0 = R0*R0;
    return R0 + (1-R0)*std::pow(1-Cosine, 5);
}
