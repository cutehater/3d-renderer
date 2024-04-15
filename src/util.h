#ifndef UTIL_H
#define UTIL_H

#include <SFML/Graphics.hpp>

namespace ScratchRenderer {
inline sf::Color operator*(const sf::Color &color, double coef) {
    sf::Color res = color;
    res.r *= coef;
    res.g *= coef;
    res.b *= coef;
    return res;
}
} // namespace ScratchRenderer

#endif // UTIL_H
