#ifndef UTILS_H
#define UTILS_H

#include <random>

template<typename T>
class Vec;

class Utils
{
private:
    static std::mt19937 Mt;
    static std::uniform_real_distribution<double> RZeroToOne;
    static std::uniform_real_distribution<double> RMinusOneToPlusOne;

public:
    static Vec<float> RandInUnitSphere();
    static Vec<float> Reflect(const Vec<float>& V, const Vec<float>& N);
    static bool Refract(const Vec<float>& V, const Vec<float>& N, float NiOverNt, Vec<float>& Refracted);
    static float Schlink(const float Cosine, const float RefIdx);
    inline static double RandZeroToOne()
    {
        return Utils::RZeroToOne(Utils::Mt);
    }

    inline static double RandMinusOneToPlusOne()
    {
        return Utils::RMinusOneToPlusOne(Utils::Mt);
    }
};

#endif // UTILS_H

