#include "primitives.h"
#include "glm/geometric.hpp"

namespace RendererProject {
namespace Primitives {
Ray::Ray(const glm::dvec3 &origin, const glm::dvec3 &direction)
    : origin_(origin), direction_(direction){};

Triangle::Triangle(const glm::dvec3 &a, const glm::dvec3 &b,
                   const glm::dvec3 &c)
    : a_(a), b_(b), c_(c){};

Plane::Plane(const glm::dvec3 &a, const glm::dvec3 &b, const glm::dvec3 &c)
    : Plane(glm::normalize(glm::cross(c - a, b - a)), a){};

Plane::Plane(const glm::dvec3 &norm, double distFromOrigin)
    : norm_(norm), distFromOrigin_(distFromOrigin){};

Plane::Plane(const glm::dvec3 &norm, const glm::dvec3 &p)
    : norm_(norm), distFromOrigin_(glm::dot(p, norm)){};
} // namespace Primitives
} // namespace RendererProject