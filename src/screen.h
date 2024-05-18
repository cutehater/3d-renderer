#ifndef SCREEN_H
#define SCREEN_H

#include "global_usings.h"
#include "primitives.h"

#include <SFML/Graphics.hpp>
#include <vector>

namespace ScratchRenderer {
class Screen {
public:
    Screen(size_t width, size_t height);

    const std::vector<sf::Vertex> &getDrawData() const;

    void setPixel(size_t i, size_t j, const Color &color);
    bool isPixelValid(size_t i, size_t j) const;

    size_t getWidth() const;
    size_t getHeight() const;

private:
    size_t width_;
    size_t height_;
    std::vector<sf::Vertex> data_;
};
} // namespace ScratchRenderer

#endif
