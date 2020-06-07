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

Vec<float> Utils::Refrect(const Vec<float>& V, const Vec<float>& N)
{
    return V - 2*V.Dot(N)*N;
}

double Utils::RandZeroToOne()
{
    return Utils::RZeroToOne(Utils::Mt);
}

double Utils::RandMinusOneToPlusOne()
{
    return Utils::RMinusOneToPlusOne(Utils::Mt);
}
