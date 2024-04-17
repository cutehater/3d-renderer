#include "screen.h"

namespace ScratchRenderer {
Screen::Screen(size_t width, size_t height) : width_(width), height_(height) {
    data_.reserve(width * height);
}

DiscreteVector2
Screen::projectVertexToScreenAndDiscretize(const Primitives::Vertex &v) const {
    auto cutToScreen = [](double value, const size_t bound) {
        return std::max(0.0, std::min(value, bound - 1.0));
    };
    double x = cutToScreen((v.getPosition().x + 1) / 2 * width_, width_);
    double y = cutToScreen((v.getPosition().y + 1) / 2 * height_, height_);
    return sf::Vector2i{x, y};
}

void Screen::setPixel(size_t i, size_t j, const Color &color) {
    if (isPixelValid(i, j)) {
        data_.emplace_back(sf::Vertex(sf::Vector2f(i, height_ - j), color));
    }
}

bool Screen::isPixelValid(size_t i, size_t j) const {
    return 0 <= i && i < height_ && 0 <= j && j < width_;
}

const std::vector<sf::Vertex> &Screen::getDrawData() const { return data_; }

size_t Screen::getWidth() const { return width_; }

size_t Screen::getHeight() const { return height_; }

void Screen::clear() { data_.clear(); }

} // namespace ScratchRenderer
