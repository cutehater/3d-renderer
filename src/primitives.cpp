#include "primitives.h"

namespace ScratchRenderer {
namespace Primitives {
Vertex::Vertex(const glm::dvec4 &pos, const glm::dvec3 &norm,
               const glm::dvec2 &texture, const glm::dvec4 &color)
    : pos_(pos), norm_(norm), texture_(texture), color_(color){};

Ray::Ray(const glm::dvec3 &origin, const glm::dvec3 &direction)
    : origin_(origin), direction_(direction){};

glm::dvec3 Ray::getOrigin() const { return origin_; }

glm::dvec3 Ray::getDirection() const { return direction_; }

Triangle::Triangle(const Vertex &a, const Vertex &b, const Vertex &c)
    : vertices_({a, b, c}){};

std::vector<Vertex> Triangle::getVertices() const { return vertices_; }

// assuming the last coordinate is equal to 1
std::vector<glm::dvec3> Triangle::getVerticesPositions() const {
    std::vector<glm::dvec3> positions;
    for (const Vertex &v : vertices_) {
        positions.push_back(v.getPosition());
    }
    return positions;
}

Plane::Plane(const glm::dvec3 &a, const glm::dvec3 &b, const glm::dvec3 &c)
    : Plane(glm::normalize(glm::cross(c - a, b - a)), a){};

Plane::Plane(const glm::dvec3 &norm, double distFromOrigin)
    : norm_(norm), distFromOrigin_(distFromOrigin){};

Plane::Plane(const glm::dvec3 &norm, const glm::dvec3 &p)
    : norm_(norm), distFromOrigin_(glm::dot(p, norm)){};

// assuming the last coordinate is equal to 1
Plane::Plane(const Triangle &triangle)
    : Plane(triangle.getVertices()[0].getPosition(),
            triangle.getVertices()[1].getPosition(),
            triangle.getVertices()[2].getPosition()){};

glm::dvec3 Plane::getNorm() const { return norm_; }

double Plane::getDistFromOrigin() const { return distFromOrigin_; }
} // namespace Primitives
} // namespace ScratchRenderer