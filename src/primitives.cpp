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

const Vector4 &Vertex::getPosition() const { return position_; }

const Color &Vertex::getColor() const { return color_; }

Vertex Vertex::interpolate(const Vertex &a, const Vertex &b, double coef) {
    return Vertex(a.position_ + (b.position_ - a.position_) * coef,
                  a.color_ + (b.color_ - a.color_) * coef);
}

Triangle::Triangle(const Vertex &a, const Vertex &b, const Vertex &c)
    : vertices_{a, b, c} {
    assert(a != b && a != c && b != c && "Triangle vertices are equal");
    reorderVertices();
};

Triangle::Triangle(const std::array<Vertex, 3> vertices) : vertices_(vertices) {
    assert(vertices[0] != vertices[1] && vertices[1] != vertices[2] &&
           vertices[0] != vertices[2] && "Triangle vertices are equal");
    reorderVertices();
}

const std::array<Vertex, 3> &Triangle::getYOrderedVertices() const {
    return vertices_;
}

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

const Vector4 &
Triangle::TrianglePositionsView::ConstIterator::operator*() const {
    return iter_->getPosition();
}

Triangle::TrianglePositionsView::ConstIterator &
Triangle::TrianglePositionsView::ConstIterator::operator++() {
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

Triangle::TrianglePositionsView::ConstIterator
Triangle::TrianglePositionsView::begin() const {
    return ConstIterator(host_.begin());
}

Triangle::TrianglePositionsView::ConstIterator
Triangle::TrianglePositionsView::end() const {
    return ConstIterator(host_.end());
}

size_t Triangle::TrianglePositionsView::size() const { return host_.size(); }

const Vector4 &Triangle::TrianglePositionsView::operator[](size_t index) const {
    assert(index < this->size() &&
           "Triangle vertex position index is out of range");
    return host_[index].getPosition();
}

} // namespace Primitives
} // namespace ScratchRenderer
