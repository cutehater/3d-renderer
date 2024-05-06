#ifndef GLOBAL_USINGS_H
#define GLOBAL_USINGS_H

#include "glm/ext/scalar_constants.hpp"
#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"

#include <SFML/Graphics.hpp>

namespace ScratchRenderer {

using DiscreteVector2 = sf::Vector2i;
using Vector3 = glm::dvec3;
using Matrix4 = glm::dmat4;
using Color = sf::Color;

static constexpr Matrix4 IdentityMatrix = glm::dmat4(1.0);
static constexpr double Epsilon = 1e-9;
static const sf::Color DefaultColor = sf::Color::White;

class Axe {
public:
    static constexpr Vector3 X = Vector3(1, 0, 0);
    static constexpr Vector3 Y = Vector3(0, 1, 0);
    static constexpr Vector3 Z = Vector3(0, 0, 1);
};

} // namespace ScratchRenderer

#endif // GLOBAL_USINGS_H
