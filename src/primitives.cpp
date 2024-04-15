#include "primitives.h"

#include "glm/ext/scalar_relational.hpp"
#include "glm/geometric.hpp"
#include "util.h"
#include <cassert>

namespace ScratchRenderer {
namespace Primitives {
Vertex::Vertex(const Vector4 &position) : position_(position){};

Vertex::Vertex(const Vector4 &position, const Color &color)
    : position_(position), color_(color){};

bool Vertex::operator==(const Vertex &other) const {
    return position_ == other.position_;
}

bool Vertex::operator!=(const Vertex &other) const { return !(*this == other); }

Vector4 &Vertex::getPosition() { return position_; }

Color &Vertex::getColor() { return color_; }

Vertex Vertex::interpolate(const Vertex &a, const Vertex &b, double coef) {
    return Vertex(a.position_ + (b.position_ - a.position_) * coef,
                  a.color_ + (b.color_ - a.color_) * coef);
}

Triangle::Triangle(const Vertex &a, const Vertex &b, const Vertex &c)
    : vertices_{a, b, c} {
    assert(a != b && a != c && b != c && "Triangle vertices are equal");
};

const std::array<Vertex, 3> &Triangle::getVertices() const { return vertices_; }

Triangle::TrianglePositionsRef Triangle::getVerticesPositions() {
    return TrianglePositionsRef(&vertices_);
}

Vector4 &Triangle::TrianglePositionsRef::Iterator::operator*() {
    return iter_->getPosition();
}

Triangle::TrianglePositionsRef::Iterator &
Triangle::TrianglePositionsRef::Iterator::operator++() {
    ++iter_;
    return *this;
}

Triangle::TrianglePositionsRef::Iterator
Triangle::TrianglePositionsRef::Iterator::operator++(int) {
    Iterator tmp = *this;
    ++iter_;
    return tmp;
}

bool Triangle::TrianglePositionsRef::Iterator::operator==(
    Triangle::TrianglePositionsRef::Iterator other) const {
    return iter_ == other.iter_;
}

bool Triangle::TrianglePositionsRef::Iterator::operator!=(
    Triangle::TrianglePositionsRef::Iterator other) const {
    return iter_ != other.iter_;
}

Triangle::TrianglePositionsRef::Iterator
Triangle::TrianglePositionsRef::begin() const {
    return Iterator(host_->begin());
}

Triangle::TrianglePositionsRef::Iterator
Triangle::TrianglePositionsRef::end() const {
    return Iterator(host_->end());
}

size_t Triangle::TrianglePositionsRef::size() const { return host_->size(); }

Vector4 &Triangle::TrianglePositionsRef::operator[](size_t index) const {
    assert(index < this->size() &&
           "Triangle vertex position index is out of range");
    return (*host_)[index].getPosition();
}

} // namespace Primitives
} // namespace ScratchRenderer
