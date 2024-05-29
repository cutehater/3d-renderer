#include "object.h"

#include "glm/ext.hpp"

#include <cassert>

namespace ScratchRenderer {
Object::Object(std::vector<Primitives::Triangle> &&triangles) : triangles_(std::move(triangles)) {}

const std::vector<Primitives::Triangle> &Object::getTriangles() const { return triangles_; }

void Object::translate(const Vector3 &axe, double length) {
    Matrix4 translatonMatrix = glm::translate(IdentityMatrix, axe * length);
    for (size_t i = 0; i < triangles_.size(); ++i) {
        triangles_[i] = Primitives::Triangle::linearTransform(translatonMatrix, triangles_[i]);
    }
}

void Object::rotate(const Vector3 &axe, double angle) {
    assert(!glm::equal(glm::length(axe), 0.0, Epsilon) &&
           "object rotation vector should have positive length");
    Matrix4 rotationMatrix = glm::rotate(IdentityMatrix, angle, axe);
    for (size_t i = 0; i < triangles_.size(); ++i) {
        triangles_[i] = Primitives::Triangle::linearTransform(rotationMatrix, triangles_[i]);
    }
}
} // namespace ScratchRenderer
