#ifndef MATERIAL_H
#define MATERIAL_H

struct HitRecord;
struct Color;
class Ray;

class Material
{
public:
    virtual ~Material() = 0;

    virtual bool Scatter(const Ray& RIn, const HitRecord& Rec, Color& Attenuation, Ray& Scattered) const = 0;
};

#endif // MATERIAL_H

