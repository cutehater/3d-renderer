#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <glm/vec3.hpp>

namespace RendererProject {
namespace Primitives {
class Ray {
public:
  Ray() = default;
  Ray(const glm::dvec3 &origin, const glm::dvec3 &direction);

private:
  glm::dvec3 origin_;
  glm::dvec3 direction_;
};

class Triangle {
public:
  Triangle() = default;
  Triangle(const glm::dvec3 &a, const glm::dvec3 &b, const glm::dvec3 &c);

private:
  glm::dvec3 a_;
  glm::dvec3 b_;
  glm::dvec3 c_;
};

class Plane {
public:
  Plane() = default;
  Plane(const glm::dvec3 &a, const glm::dvec3 &b, const glm::dvec3 &c);
  Plane(const glm::dvec3 &norm, double distFromOrigin);
  Plane(const glm::dvec3 &norm, const glm::dvec3 &p);

private:
  glm::dvec3 norm_;
  double distFromOrigin_;
};
} // namespace Primitives
} // namespace RendererProject

#endif // PRIMITIVES_H