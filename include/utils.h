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
    static Vec<float> Refrect(const Vec<float>& V, const Vec<float>& N);
    static double RandZeroToOne();
    static double RandMinusOneToPlusOne();
};

#endif // UTILS_H

