#include "object.h"

namespace ScratchRenderer {
Object::Object(std::vector<Primitives::Triangle> triangles)
    : triangles_(std::move(triangles)) {}

const std::vector<Primitives::Triangle> &Object::getTriangles() {
    return triangles_;
}
} // namespace ScratchRenderer
