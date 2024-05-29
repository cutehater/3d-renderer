#include "screen.h"

namespace ScratchRenderer {
Screen::Screen(size_t width, size_t height) : width_(width), height_(height) { data_.resize(width * height); }

const std::vector<sf::Vertex> &Screen::getDrawData() const { return data_; }

void Screen::setPixel(size_t i, size_t j, const Color &color) {
    if (isPixelValid(i, j)) {
        data_[i * height_ + j] = sf::Vertex(sf::Vector2f(i, height_ - j), color);
    }
}

bool Screen::isPixelValid(size_t i, size_t j) const { return 0 <= i && i < width_ && 0 <= j && j < height_; }

size_t Screen::getWidth() const { return width_; }

size_t Screen::getHeight() const { return height_; }

} // namespace ScratchRenderer
