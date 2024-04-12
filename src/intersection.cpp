#include "intersection.h"

#include "glm/common.hpp"
#include "glm/ext/scalar_relational.hpp"
#include "glm/geometric.hpp"

namespace ScratchRenderer {

Intersection intersectRayPlane(const Primitives::Ray &ray,
                               const Primitives::Plane &plane) {
    double orientedRayPlaneDistance =
        glm::dot(plane.getNormal(), ray.getOrigin()) -
        plane.getOrientedDistFromOrigin();
    double normalsAngle = glm::dot(plane.getNormal(), ray.getDirection());

    if (glm::equal(normalsAngle, 0.0, Epsilon)) {
        if (glm::equal(orientedRayPlaneDistance, 0.0, Epsilon)) {
            return Intersection{Intersection::Type::Coincide, ray.getOrigin()};
        } else {
            return Intersection{Intersection::Type::NonIntersect};
        }
    } else {
        double orientedDistance = -orientedRayPlaneDistance / normalsAngle;
        if (orientedDistance < 0.0) {
            return Intersection{Intersection::Type::NonIntersect};
        } else {
            return Intersection{Intersection::Type::Intersect,
                                ray.getOrigin() +
                                    ray.getDirection() * orientedDistance};
        }
    }
}

} // namespace ScratchRenderer
