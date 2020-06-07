#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>
#include <cstdint>
#include <algorithm>
#include <stdexcept>

#include <color.h>

template<typename T>
class Vec
{
public:
    T E[3] = { 0, 0, 0 };

    Vec() {}
    Vec(T X) { E[0] = X, E[1] = X, E[2] = X; }
    Vec(T X, T Y, T Z) { E[0] = X, E[1] = Y, E[2] = Z; }

    inline T X() const { return E[0]; }
    inline T Y() const { return E[1]; }
    inline T Z() const { return E[2]; }

    Vec<T> Normalize() const
    {
        T Nor2 = SquaredLength();
        Vec<T> RetV(0);
        if (Nor2 > 0)
        {
            T InvNor = 1 / std::sqrt(Nor2);
            RetV.E[0] = E[0] * InvNor;
            RetV.E[1] = E[1] * InvNor;
            RetV.E[2] = E[2] * InvNor;
        }
        return RetV;
    }

    inline const Vec<T>& operator+ () const { return *this; }
    inline Vec<T>& operator- () const { return Vec<T>(-X(), -Y(), -Z()); }
    inline T operator[] (int i) const { return E[i]; }
    inline T& operator[] (int i) { return E[i]; };

    template<typename CastType>
    inline operator Vec<CastType>() const {
        return Vec<CastType>(E[0], E[1], E[2]);
    }

    Vec<T>& operator+= (const Vec<T>& V)
    {
        E[0] += V.E[0];
        E[1] += V.E[1];
        E[2] += V.E[2];
        return *this;
    }
    Vec<T>& operator-= (const Vec<T>& V)
    {
        E[0] -= V.E[0];
        E[1] -= V.E[1];
        E[2] -= V.E[2];
        return *this;
    }
    Vec<T>& operator*= (const Vec<T>& V)
    {
        E[0] *= V.E[0];
        E[1] *= V.E[1];
        E[2] *= V.E[2];
        return *this;
    }
    Vec<T>& operator/= (const Vec<T>& V)
    {
        E[0] /= V.E[0];
        E[1] /= V.E[1];
        E[2] /= V.E[2];
        return *this;
    }
    Vec<T>& operator*= (const double Val)
    {
        E[0] *= Val;
        E[1] *= Val;
        E[2] *= Val;
        return *this;
    }
    Vec<T>& operator/= (const double Val)
    {
        E[0] /= Val;
        E[1] /= Val;
        E[2] /= Val;
        return *this;
    }

    Vec<T>& operator+= (const Color& C)
    {
        E[0] += C.R;
        E[1] += C.G;
        E[2] += C.B;
        return *this;
    }

    Vec<T>& operator-= (const Color& C)
    {
        E[0] -= C.R;
        E[1] -= C.G;
        E[2] -= C.B;
        return *this;
    }

    T Dot(const Vec<T> &V) const {
        return X() * V.X() + Y() * V.Y() + Z() * V.Z();
    }
    Vec<T> Cross(const Vec<T> &V) const
    {
        return Vec<T>(
                (E[1] * V[2] - E[2] * V[1]),
                -(E[0] * V[2] - E[2] * V[0]),
                (E[0] * V[1] - E[1] * V[0]));
    }

    T SquaredLength() const { return X() * X() + Y() * Y() + Z() * Z(); }
    T Length() const { return std::sqrt(SquaredLength()); }

    Color ToColor() const
    {
        return Color(
                std::clamp<std::uint8_t>(X(), 0, 255),
                std::clamp<std::uint8_t>(Y(), 0, 255),
                std::clamp<std::uint8_t>(Z(), 0, 255)
                );
    }
};

template <typename T>
inline std::ostream& operator << (std::ostream& Os, const Vec<T>& V)
{
    Os << "[" << +V.X() << " " << +V.Y() << " " << +V.Z() << "]";
    return Os;
}

template <typename T>
inline Vec<T> operator+(const Vec<T> &V1, const Vec<T> &V2)
{
    return Vec<T>(V1.X() + V2.X(), V1.Y() + V2.Y(), V1.Z() + V2.Z());
}

template <typename T>
inline Vec<T> operator-(const Vec<T> &V1, const Vec<T> &V2)
{
    return Vec<T>(V1.X() - V2.X(), V1.Y() - V2.Y(), V1.Z() - V2.Z());
}

template <typename T>
inline Vec<T> operator*(const Vec<T> &V1, const Vec<T> &V2)
{
    return Vec<T>(V1.X() * V2.X(), V1.Y() * V2.Y(), V1.Z() * V2.Z());
}

template <typename T>
inline Vec<T> operator/(const Vec<T> &V1, const Vec<T> &V2)
{
    return Vec<T>(V1.X() / V2.X(), V1.Y() / V2.Y(), V1.Z() / V2.Z());
}

template <typename T>
inline Vec<T> operator*(const double Val, const Vec<T> &V)
{
    return Vec<T>(Val * V.X(), Val * V.Y(), Val * V.Z());
}

template <typename T>
inline Vec<T> operator*(const Vec<T> &V, const double Val)
{
    return Vec<T>(Val * V.X(), Val * V.Y(), Val * V.Z());
}

template <typename T>
inline Vec<T> operator+(const double Val, const Vec<T> &V)
{
    return Vec<T>(V.X() + Val, V.Y() + Val, V.Z() + Val);
}

template <typename T>
inline Vec<T> operator+(const Vec<T> &V, const double Val)
{
    return Vec<T>(V.X() + Val, V.Y() + Val, V.Z() + Val);
}

template <typename T>
inline Vec<T> operator-(const double Val, const Vec<T> &V)
{
    return Vec<T>(V.X() - Val, V.Y() - Val, V.Z() - Val);
}

template <typename T>
inline Vec<T> operator-(const Vec<T> &V, const double Val)
{
    return Vec<T>(V.X() - Val, V.Y() - Val, V.Z() - Val);
}

template <typename T>
inline Vec<T> operator/(const Vec<T> &V, const double Val)
{
    return Vec<T>(V.X() / Val, V.Y() / Val, V.Z() / Val);
}

#endif // VEC3_H
