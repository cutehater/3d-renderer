#include "primitives.h"

namespace ScratchRenderer {
namespace Primitives {
Vertex::Vertex(const glm::dvec4 &pos, const glm::dvec3 &norm,
               const glm::dvec2 &texture, const glm::dvec3 &color)
    : pos_(pos), norm_(norm), texture_(texture), color_(color){};

Vertex::Vertex(const Triangle &triangle, const glm::dvec4 &pos) : pos_(pos) {
    std::vector<double> w = triangle.getBarycentricWeights(pos);
    std::vector<Vertex> v = triangle.getVertices();
    for (size_t i = 0; i < v.size(); ++i) {
        norm_ += w[i] * v[i].getNorm();
        texture_ += w[i] * v[i].getTexture();
        color_ += w[i] * v[i].getColor();
    }
}

glm::dvec4 Vertex::getPosition() const { return pos_; }

glm::dvec3 Vertex::getNorm() const { return norm_; }

glm::dvec2 Vertex::getTexture() const { return texture_; }

glm::dvec3 Vertex::getColor() const { return color_; }

Ray::Ray(const glm::dvec3 &origin, const glm::dvec3 &direction)
    : origin_(origin), direction_(direction){};

glm::dvec3 Ray::getOrigin() const { return origin_; }

glm::dvec3 Ray::getDirection() const { return direction_; }

Triangle::Triangle(const Vertex &a, const Vertex &b, const Vertex &c)
    : vertices_({a, b, c}){};

std::vector<Vertex> Triangle::getVertices() const { return vertices_; }

std::vector<double> Triangle::getBarycentricWeights(glm::dvec3 p) const {
    std::vector<glm::dvec3> vertices = getVerticesPositions();

    glm::dvec3 r = p - vertices[0];
    glm::dvec3 q1 = vertices[1] - vertices[0];
    glm::dvec3 q2 = vertices[2] - vertices[0];
    double mult = 1.0 / (glm::dot(q1, q1) * glm::dot(q2, q2) -
                         glm::dot(q1, q2) * glm::dot(q1, q2));

    std::vector<double> weights(3);
    weights[1] = mult * (glm::dot(q2, q2) * glm::dot(r, q1) -
                         glm::dot(q1, q2) * glm::dot(r, q2));
    weights[2] = mult * (glm::dot(q1, q1) * glm::dot(r, q2) -
                         glm::dot(q1, q2) * glm::dot(r, q1));
    weights[0] = 1 - weights[1] - weights[2];

    return weights;
}

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