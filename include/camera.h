#ifndef CAMERA_H
#define CAMERA_H

#include "vec.h"
class Ray;

class Camera
{
public:
    Vec<float> LowerLeftCorner;
    Vec<float> Horizonal;
    Vec<float> Vertical;
    Vec<float> Origin;

    Camera()
    {
        LowerLeftCorner = Vec<float>(-2.0, -1.0, -1.0);
        Horizonal = Vec<float>(4.0, 0.0, 0.0);
        Vertical = Vec<float>(0.0, 2.0, 0.0);
        Origin = Vec<float>(0.0, 0.0, 0.0);
    }

    Ray GetRay(float U, float V) const;
};

#endif // CAMERA_H
