#include "color.h"

 Color operator*(const float Val, const Color &C)
{
    return Color(Val * C.R, Val * C.G, Val * C.B, Val * C.A);
}

Color operator/(const Color &C, const float Val)
{
    return Color(C.R / Val, C.G / Val, C.B / Val, C.A / Val);
}

Color operator+(const Color &C1, const Color &C2)
{
    return Color(C1.R + C2.R, C1.G + C2.G, C1.B + C2.B);
}

Color operator-(const Color &C1, const Color &C2)
{
    return Color(C1.R - C2.R, C1.G - C2.G, C1.B - C2.B);
}

Color operator*(const Color &C1, const Color &C2)
{
    return Color(C1.R * C2.R, C1.G * C2.G, C1.B * C2.B);
}
