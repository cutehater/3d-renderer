#include "primitives.h"

#include "math_functions.h"

#include "glm/ext/scalar_relational.hpp"
#include "glm/geometric.hpp"
#include <cassert>

namespace ScratchRenderer {
namespace Primitives {
Vertex::Vertex(const Vector3 &position, const Vector3 &normal,
               const Vector2 &texture, const Vector3 &color)
    : position_(position), normal_(normal), texture_(texture), color_(color){};

Vertex Vertex::interpolateVertexInsideTriangle(const Triangle &triangle,
                                               const Vector3 &position) {
    std::array<double, 3> weights =
        triangle.getBarycentricCoordinates(position);
    assert(weights[0] > -Epsilon && weights[1] > -Epsilon &&
           weights[2] > -Epsilon && "Interpolating vertex is outside triangle");

    Vertex v;
    v.position_ = position;
    std::array<Vertex, 3> triangleVertices = triangle.getVertices();
    for (size_t i = 0; i < triangleVertices.size(); ++i) {
        v.normal_ += weights[i] * triangleVertices[i].getNormal();
        v.texture_ += weights[i] * triangleVertices[i].getTexture();
        v.color_ += weights[i] * triangleVertices[i].getColor();
    }

    return v;
}

bool Vertex::operator==(const Vertex &other) const {
    return glm::equal(position_, other.position_, Epsilon);
}

bool Vertex::operator!=(const Vertex &other) const { return !(*this == other); }

Vector3 Vertex::getPosition() const { return position_; }

Vector3 Vertex::getNormal() const { return normal_; }

Vector2 Vertex::getTexture() const { return texture_; }

Vector3 Vertex::getColor() const { return color_; }

Ray::Ray(const Vector3 &origin, const Vector3 &direction)
    : origin_(origin), direction_(direction) {
    assert(!glm::equal(direction, ZeroVector3, Epsilon) &&
           "Ray has zero direction vector");
};

Vector3 Ray::getOrigin() const { return origin_; }

Vector3 Ray::getDirection() const { return direction_; }

Triangle::Triangle(const Vertex &a, const Vertex &b, const Vertex &c)
    : vertices_{a, b, c} {
    assert(a != b && a != c && b != c && "Triangle vertices are equal");
};

const std::array<Vertex, 3> &Triangle::getVertices() const { return vertices_; }

const std::array<double, 3> &
Triangle::getBarycentricCoordinates(const Vector3 &p) const {
    TrianglePositionsView vertices = getVerticesPositions();

    Vector3 r = p - vertices[0];
    Vector3 q1 = vertices[1] - vertices[0];
    Vector3 q2 = vertices[2] - vertices[0];
    Vector2 rq(glm::dot(r, q1), glm::dot(r, q2));

    double mult = 1.0 / Math::GetParallelogramAreaSquare(q1, q2);

    std::array<double, 3> weights;
    weights[1] =
        mult * glm::dot(Vector2(glm::dot(q2, q2), -glm::dot(q1, q2)), rq);
    weights[2] =
        mult * glm::dot(Vector2(-glm::dot(q1, q2), glm::dot(q1, q1)), rq);
    weights[0] = 1 - weights[1] - weights[2];

    return weights;
}

Triangle::TrianglePositionsView Triangle::getVerticesPositions() const {
    return TrianglePositionsView(&vertices_);
}

Plane::Plane(const Vector3 &a, const Vector3 &b, const Vector3 &c) {
    Vector3 crossProduct = glm::cross(c - a, b - a);
    assert(!glm::equal(crossProduct, ZeroVector3, Epsilon) &&
           "Some of points for construsting plane are same");
    normal_ = glm::normalize(crossProduct);
    orientedDistFromOrigin_ = glm::dot(a, normal_);
};

Plane::Plane(const Vector3 &normal, double distFromOrigin)
    : orientedDistFromOrigin_(distFromOrigin) {
    assert(!glm::equal(normal, ZeroVector3, Epsilon) &&
           "Plane has zero normal vector");
    normal_ = glm::normalize(normal);
};

Plane::Plane(const Vector3 &normal, const Vector3 &p) {
    assert(!glm::equal(normal, ZeroVector3, Epsilon) &&
           "Plane has zero normal vector");
    normal_ = glm::normalize(normal);
    orientedDistFromOrigin_ = glm::dot(p, normal_);
};

Plane::Plane(const Triangle &triangle)
    : Plane(triangle.getVertices()[0].getPosition(),
            triangle.getVertices()[1].getPosition(),
            triangle.getVertices()[2].getPosition()){};

Vector3 Plane::getNormal() const { return normal_; }

double Plane::getOrientedDistFromOrigin() const {
    return orientedDistFromOrigin_;
}
} // namespace Primitives
} // namespace ScratchRenderer
