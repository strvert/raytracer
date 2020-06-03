#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>
#include <cstdint>
#include <stdexcept>

template<typename T>
class Vec3
{
public:
    T E[4] = { 0, 0, 0, 255 };

    Vec3() {}
    Vec3(T X) { E[0] = X, E[1] = X, E[2] = X; }
    Vec3(T X, T Y, T Z) { E[0] = X, E[1] = Y, E[2] = Z; }

    inline T X() const { return E[0]; }
    inline T Y() const { return E[1]; }
    inline T Z() const { return E[2]; }
    inline T R() const { return E[0]; }
    inline T G() const { return E[1]; }
    inline T B() const { return E[2]; }

    Vec3<T> Normalize() const
    {
        T Nor2 = SquaredLength();
        Vec3<T> RetV(0);
        if (Nor2 > 0)
        {
            T InvNor = 1 / std::sqrt(Nor2);
            RetV.E[0] = E[0] * InvNor;
            RetV.E[1] = E[1] * InvNor;
            RetV.E[2] = E[2] * InvNor;
        }
        return RetV;
    }

    inline const Vec3<T>& operator+ () const { return *this; }
    inline Vec3<T>& operator- () const { return Vec3<T>(-X(), -Y(), -Z()); }
    inline T operator[] (int i) const { return E[i]; }
    inline T& operator[] (int i) { return E[i]; };

    template<typename CastType>
    inline operator Vec3<CastType>() const {
        return Vec3<CastType>(E[0], E[1], E[2]);
    }

    Vec3<T>& operator+= (const Vec3<T>& V)
    {
        E[0] += V.E[0];
        E[1] += V.E[1];
        E[2] += V.E[2];
        return *this;
    }
    Vec3<T>& operator-= (const Vec3<T>& V)
    {
        E[0] -= V.E[0];
        E[1] -= V.E[1];
        E[2] -= V.E[2];
        return *this;
    }
    Vec3<T>& operator*= (const Vec3<T>& V)
    {
        E[0] *= V.E[0];
        E[1] *= V.E[1];
        E[2] *= V.E[2];
        return *this;
    }
    Vec3<T>& operator/= (const Vec3<T>& V)
    {
        E[0] /= V.E[0];
        E[1] /= V.E[1];
        E[2] /= V.E[2];
        return *this;
    }
    Vec3<T>& operator*= (const double Val)
    {
        E[0] *= Val;
        E[1] *= Val;
        E[2] *= Val;
        return *this;
    }
    Vec3<T>& operator/= (const double Val)
    {
        E[0] /= Val;
        E[1] /= Val;
        E[2] /= Val;
        return *this;
    }

    T Dot(const Vec3<T> &V) const {
        return X() * V.X() + Y() * V.Y() + Z() * V.Z();
    }
    Vec3<T> Cross(const Vec3<T> &V) const
    {
        return Vec3<T>(
                (E[1] * V[2] - E[2] * V[1]),
                -(E[0] * V[2] - E[2] * V[0]),
                (E[0] * V[1] - E[1] * V[0]));
    }

    T SquaredLength() const { return X() * X() + Y() * Y() + Z() * Z(); }
    T Length() const { return std::sqrt(SquaredLength()); }
};

template <typename T>
inline std::ostream& operator << (std::ostream& Os, const Vec3<T>& V)
{
    Os << "[" << +V.X() << " " << +V.Y() << " " << +V.Z() << "]";
    return Os;
}

template <typename T>
inline Vec3<T> operator+(const Vec3<T> &V1, const Vec3<T> &V2)
{
    return Vec3<T>(V1.X() + V2.X(), V1.Y() + V2.Y(), V1.Z() + V2.Z());
}

template <typename T>
inline Vec3<T> operator-(const Vec3<T> &V1, const Vec3<T> &V2)
{
    return Vec3<T>(V1.X() - V2.X(), V1.Y() - V2.Y(), V1.Z() - V2.Z());
}

template <typename T>
inline Vec3<T> operator*(const Vec3<T> &V1, const Vec3<T> &V2)
{
    return Vec3<T>(V1.X() * V2.X(), V1.Y() * V2.Y(), V1.Z() * V2.Z());
}

template <typename T>
inline Vec3<T> operator/(const Vec3<T> &V1, const Vec3<T> &V2)
{
    return Vec3<T>(V1.X() / V2.X(), V1.Y() / V2.Y(), V1.Z() / V2.Z());
}

template <typename T>
inline Vec3<T> operator*(const double Val, const Vec3<T> &V)
{
    return Vec3<T>(Val * V.X(), Val * V.Y(), Val * V.Z());
}

template <typename T>
inline Vec3<T> operator+(const double Val, const Vec3<T> &V)
{
    return Vec3<T>(V.X() + Val, V.Y() + Val, V.Z() + Val);
}

template <typename T>
inline Vec3<T> operator+(const Vec3<T> &V, const double Val)
{
    return Vec3<T>(V.X() + Val, V.Y() + Val, V.Z() + Val);
}

template <typename T>
inline Vec3<T> operator-(const double Val, const Vec3<T> &V)
{
    return Vec3<T>(V.X() - Val, V.Y() - Val, V.Z() - Val);
}

template <typename T>
inline Vec3<T> operator-(const Vec3<T> &V, const double Val)
{
    return Vec3<T>(V.X() - Val, V.Y() - Val, V.Z() - Val);
}

template <typename T>
inline Vec3<T> operator/(const Vec3<T> &V, const double Val)
{
    return Vec3<T>(V.X() / Val, V.Y() / Val, V.Z() / Val);
}

template <typename T>
inline Vec3<T> operator*(const Vec3<T> &V, const double Val)
{
    return Vec3<T>(Val * V.X(), Val * V.Y(), Val * V.Z());
}

using Vec3f = Vec3<float>;
using Vec3d = Vec3<double>;
using Vec3i = Vec3<int>;

#endif // VEC3_H


