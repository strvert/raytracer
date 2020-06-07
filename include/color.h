#ifndef COLOR_H
#define COLOR_H

#include <cstdint>

struct Color
{
    float R;
    float G;
    float B;
    float A;

    Color(): R(0), G(0), B(0), A(0) {}
    Color(float V): R(V), G(V), B(V), A(V) {}
    Color(float R, float G, float B): R(R), G(G), B(B), A(1) {}
    Color(float R, float G, float B, float A): R(R), G(G), B(B), A(A) {}

    static Color FromRGBA256(std::uint8_t InR, std::uint8_t InG, std::uint8_t InB, std::uint8_t InA)
    {
        return Color(InR / 255.0, InG / 255.0, InB / 255.0, InA / 255.0);
    }

    static Color FromRGBA256(std::uint8_t InR, std::uint8_t InG, std::uint8_t InB)
    {
        return Color(InR / 255.0, InG / 255.0, InB / 255.0, 1.0);
    }

    std::uint8_t R256() { return R * 255; }
    std::uint8_t G256() { return G * 255; }
    std::uint8_t B256() { return B * 255; }
    std::uint8_t A256() { return A * 255; }

    Color& operator+= (const Color& C)
    {
        R += C.R;
        G += C.G;
        B += C.B;
        A += C.A;
        return *this;
    }

    Color& operator-= (const Color& C)
    {
        R += C.R;
        G += C.G;
        B += C.B;
        A += C.A;
        return *this;
    }
};

Color operator*(const float Val, const Color &C);
Color operator/(const Color &C, const float Val);
Color operator+(const Color &C1, const Color &C2);
Color operator-(const Color &C1, const Color &C2);
Color operator*(const Color &C1, const Color &C2);

#endif // COLOR_H
