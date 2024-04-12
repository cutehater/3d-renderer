#include "object.h"

namespace ScratchRenderer {
Object::Object(std::vector<Primitives::Triangle> &&triangles)
    : triangles_(std::move(triangles)) {}

const std::vector<Primitives::Triangle> &Object::getTriangles() const {
    return triangles_;
}
} // namespace ScratchRenderer
