#include "camera.h"

#include "ray.h"

Ray Camera::GetRay(float U, float V) const {
    return Ray(Origin, (LowerLeftCorner + U*Horizonal + V*Vertical) - Origin);
}
