#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "glm/geometric.hpp"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include <vector>

namespace ScratchRenderer {
namespace Primitives {
class Vertex {
public:
    Vertex() = default;
    Vertex(const glm::dvec4 &pos, const glm::dvec3 &norm,
           const glm::dvec2 &texture, const glm::dvec3 &color);
    // constructor for interpolated vertex inside triangle
    Vertex(const Triangle &Triangle, const glm::dvec4 &pos);

    glm::dvec4 getPosition() const;
    glm::dvec3 getNorm() const;
    glm::dvec2 getTexture() const;
    glm::dvec3 getColor() const;

private:
    glm::dvec4 pos_;
    glm::dvec3 norm_;
    glm::dvec2 texture_;
    glm::dvec3 color_;
};

class Ray {
public:
    Ray() = default;
    Ray(const glm::dvec3 &origin, const glm::dvec3 &direction);

    glm::dvec3 getOrigin() const;
    glm::dvec3 getDirection() const;

private:
    glm::dvec3 origin_;
    glm::dvec3 direction_;
};

class Triangle {
public:
    Triangle() = default;
    Triangle(const Vertex &a, const Vertex &b, const Vertex &c);

    std::vector<Vertex> getVertices() const;
    std::vector<glm::dvec3> getVerticesPositions() const;
    std::vector<double> getBarycentricWeights(glm::dvec3 p) const;

private:
    std::vector<Vertex> vertices_;
};

class Plane {
public:
    Plane() = default;
    Plane(const glm::dvec3 &a, const glm::dvec3 &b, const glm::dvec3 &c);
    Plane(const glm::dvec3 &norm, double distFromOrigin);
    Plane(const glm::dvec3 &norm, const glm::dvec3 &p);
    Plane(const Triangle &triangle);

    glm::dvec3 getNorm() const;
    double getDistFromOrigin() const;

private:
    glm::dvec3 norm_;
    double distFromOrigin_;
};
} // namespace Primitives
} // namespace ScratchRenderer

#endif // PRIMITIVES_H