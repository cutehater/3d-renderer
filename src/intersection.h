#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "global_usings.h"
#include "primitives.h"
#include <vector>

namespace ScratchRenderer {
struct Intersection {
    enum class Type { Intersect, NonIntersect, Coincide };
    Type type;
    Vector3 point;
};

Intersection intersectRayPlane(const Primitives::Ray &ray,
                               const Primitives::Plane &plane);
} // namespace ScratchRenderer

#endif // INTERSECTION_H
