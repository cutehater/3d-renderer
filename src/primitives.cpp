#include "primitives.h"

#include "glm/ext/scalar_relational.hpp"

#include <cassert>

namespace ScratchRenderer {
namespace Primitives {
Vertex::Vertex(const Vector4 &position) : position_(position){};

Vertex::Vertex(const Vector4 &position, const Color &color) : position_(position), color_(color){};

bool Vertex::operator==(const Vertex &other) const { return position_ == other.position_; }

bool Vertex::operator!=(const Vertex &other) const { return !(*this == other); }

Vertex operator*(const Matrix4 &m, const Vertex &v) {
    Vector4 newPosition(m * v.getPosition());
    newPosition.normalize();
    return Vertex(newPosition, v.getColor());
}

const Vector4 &Vertex::getPosition() const { return position_; }

const Color &Vertex::getColor() const { return color_; }

void Vertex::setColor(const Color &color) { color_ = color; }

sf::Color operator*(const sf::Color color, double coef) {
    sf::Color res = color;
    res.r *= coef;
    res.g *= coef;
    res.b *= coef;
    res.a *= coef;
    return res;
}

Vertex Vertex::interpolate(const Vertex &a, const Vertex &b, double coef) {
    assert(coef >= 0.0 && coef <= 1.0 && "interpolating coefficient should be between 0 and 1");
    return Vertex(a.position_ * (1 - coef) + b.position_ * coef, a.color_ * (1 - coef) + b.color_ * coef);
}

const Vector4 &Triangle::TrianglePositionsView::ConstIterator::operator*() const {
    return iter_->getPosition();
}

Triangle::TrianglePositionsView::ConstIterator &Triangle::TrianglePositionsView::ConstIterator::operator++() {
    ++iter_;
    return *this;
}

Triangle::TrianglePositionsView::ConstIterator
Triangle::TrianglePositionsView::ConstIterator::operator++(int) {
    ConstIterator tmp = *this;
    ++iter_;
    return tmp;
}

bool Triangle::TrianglePositionsView::ConstIterator::operator==(
    Triangle::TrianglePositionsView::ConstIterator other) const {
    return iter_ == other.iter_;
}

bool Triangle::TrianglePositionsView::ConstIterator::operator!=(
    Triangle::TrianglePositionsView::ConstIterator other) const {
    return iter_ != other.iter_;
}

Triangle::TrianglePositionsView::ConstIterator Triangle::TrianglePositionsView::begin() const {
    return ConstIterator(host_.begin());
}

Triangle::TrianglePositionsView::ConstIterator Triangle::TrianglePositionsView::end() const {
    return ConstIterator(host_.end());
}

size_t Triangle::TrianglePositionsView::size() const { return host_.size(); }

const Vector4 &Triangle::TrianglePositionsView::operator[](size_t index) const {
    assert(index < this->size() && "triangle vertex position index is out of range");
    return host_[index].getPosition();
}

Triangle::Triangle(const Vertex &a, const Vertex &b, const Vertex &c) : vertices_{a, b, c} {
    reorderVertices();
};

Triangle::Triangle(const std::array<Vertex, 3> vertices) : vertices_(vertices) { reorderVertices(); }

bool Triangle::operator==(const Triangle &other) const {
    auto otherVertices = other.getYOrderedVertices();
    return vertices_[0] == otherVertices[0] && vertices_[1] == otherVertices[1] &&
           vertices_[2] == otherVertices[2];
}

bool Triangle::operator!=(const Triangle &other) const { return !(*this == other); }

const std::array<Vertex, 3> &Triangle::getYOrderedVertices() const { return vertices_; }

Triangle::TrianglePositionsView Triangle::getYOrderedVerticesPositions() const {
    return TrianglePositionsView(vertices_);
}

void Triangle::reorderVertices() {
    if (vertices_[0].getPosition().y > vertices_[1].getPosition().y) {
        std::swap(vertices_[0], vertices_[1]);
    }
    if (vertices_[1].getPosition().y > vertices_[2].getPosition().y) {
        std::swap(vertices_[1], vertices_[2]);
    }
    if (vertices_[0].getPosition().y > vertices_[1].getPosition().y) {
        std::swap(vertices_[0], vertices_[1]);
    }
}

Triangle Triangle::linearTransform(const Matrix4 &transformMatrix, const Triangle &triangle) {
    std::array<Vertex, 3> transformedVertices;
    for (size_t i = 0; i < 3; ++i) {
        transformedVertices[i] = transformMatrix * triangle.getYOrderedVertices()[i];
    }
    return Triangle(transformedVertices);
}

} // namespace Primitives
} // namespace ScratchRenderer
