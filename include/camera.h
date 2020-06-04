#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"

class Camera
{
public:
    Vec3f LowerLeftCorner;
    Vec3f Horizonal;
    Vec3f Vertical;
    Vec3f Origin;

    Camera()
    {
        LowerLeftCorner = Vec3f(-2.0, -1.0, -1.0);
        Horizonal = Vec3f(4.0, 0.0, 0.0);
        Vertical = Vec3f(0.0, 2.0, 0.0);
        Origin = Vec3f(0.0, 0.0, 0.0);
    }

    Ray GetRay(float U, float V) { return Ray(Origin, (LowerLeftCorner + U*Horizonal + V*Vertical) - Origin); }
};

#endif // CAMERA_H
