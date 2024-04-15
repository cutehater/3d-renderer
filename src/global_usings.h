#ifndef GLOBAL_USINGS_H
#define GLOBAL_USINGS_H

#include "glm/ext/scalar_constants.hpp"
#include "glm/mat4x4.hpp"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include <SFML/Graphics.hpp>

namespace ScratchRenderer {

using Vector2 = glm::dvec3;
using Vector3 = glm::dvec3;
using Matrix4 = glm::dmat4;
using Color = sf::Color;

static constexpr Vector2 ZeroVector2 = Vector2();
static constexpr Vector3 ZeroVector3 = Vector3();
static constexpr Matrix4 IdentityMatrix = glm::dmat4();
static const double Epsilon = glm::epsilon<double>();

} // namespace ScratchRenderer

#endif // GLOBAL_USINGS_H

// TODO: preconditions in every function/method
