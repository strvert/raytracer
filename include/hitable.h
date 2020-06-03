#ifndef HITABLE_H
#define HITABLE_H

#include <vector>
#include <memory>
#include "ray.h"

struct HitRecord
{
    float T;
    Vec3f P;
    Vec3f N;
};

class Hitable
{
public:
    virtual ~Hitable() = 0;
    virtual bool Hit(const Ray& R, float TMin, float TMax, HitRecord& Rec) const = 0;
};

class HitableList: public Hitable
{
private:
    std::vector<std::unique_ptr<Hitable>> List;
public:
    HitableList() {}
    virtual ~HitableList() {}

    void Add(std::unique_ptr<Hitable> Object);

    virtual bool Hit(const Ray& R, float TMin, float TMax, HitRecord& Rec) const override;
};

#endif // HITABLE_H
