#include "hitable.h"

Hitable::~Hitable() {}

void HitableList::Add(std::unique_ptr<Hitable> Object)
{
    List.push_back(std::move(Object));
}

bool HitableList::Hit(const Ray& R, float TMin, float TMax, HitRecord& Rec) const
{
    HitRecord Temp;
    bool HitAnything = false;
    double Closest = TMax;
    for (auto& Obj: List)
    {
        if (Obj->Hit(R, TMin, Closest, Temp))
        {
            HitAnything = true;
            Closest = Temp.T;
            Rec = Temp;
        }
    }
    return HitAnything;
}
