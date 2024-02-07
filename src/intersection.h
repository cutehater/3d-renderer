#ifndef CLIP_H
#define CLIP_H

#include "primitives.h"
#include <vector>

namespace ScratchRenderer {
struct Intersection {
    enum class Type { Intersect, NonIntersect, Coincide };
    Type type;
    glm::dvec3 point;
};

Intersection intersectRayPlane(const Primitives::Ray &ray,
                               const Primitives::Plane &plane);

Intersection intersectRayTriangle(const Primitives::Ray &ray,
                                  const Primitives::Triangle &triangle);

std::vector<Primitives::Triangle>
intersectTrianglePlane(const Primitives::Triangle &triangle,
                       const Primitives::Plane &plane);
} // namespace ScratchRenderer

#endif // CLIP_H