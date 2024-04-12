#include "math_functions.h"

#include "glm/geometric.hpp"

namespace ScratchRenderer {
namespace Math {
double GetParallelogramAreaSquare(const Vector3 &a, const Vector3 &b) {
    return glm::dot(a, a) * glm::dot(b, b) - glm::dot(a, b) * glm::dot(a, b);
}
} // namespace Math
} // namespace ScratchRenderer
