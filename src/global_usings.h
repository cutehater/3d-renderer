#ifndef GLOBAL_USINGS_H
#define GLOBAL_USINGS_H

#include "glm/ext/scalar_constants.hpp"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

namespace ScratchRenderer {

using Vector2 = glm::dvec2;
using Vector3 = glm::dvec3;
using Vector4 = glm::dvec4;

static constexpr Vector2 ZeroVector2 = Vector2();
static constexpr Vector3 ZeroVector3 = Vector3();
static constexpr Vector4 ZeroVector4 = Vector4();
static const double Epsilon = glm::epsilon<double>();

} // namespace ScratchRenderer

#endif // GLOBAL_USINGS_H

// TODO: preconditions in every function/method
