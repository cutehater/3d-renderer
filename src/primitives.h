#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "global_usings.h"
#include "vector4.h"

#include <SFML/Graphics.hpp>
#include <array>

namespace ScratchRenderer {
namespace Primitives {
class Vertex {
public:
    Vertex() = default;
    explicit Vertex(const Vector4 &position);
    Vertex(const Vector4 &position, const Color &color);

    bool operator==(const Vertex &other) const;
    bool operator!=(const Vertex &other) const;

    friend Vertex operator*(const Matrix4 &m, const Vertex &v);

    const Vector4 &getPosition() const;
    const Color &getColor() const;
    void setColor(const Color &color);

    static Vertex interpolate(const Vertex &a, const Vertex &b, double coef);

private:
    friend sf::Color operator*(const sf::Color color, double coef);

    Vector4 position_ = Vector4();
    Color color_ = DefaultColor;
};

class Triangle {
public:
    class TrianglePositionsView {
        using Container = std::array<Vertex, 3>;

        friend class Triangle;
        TrianglePositionsView(const Container &host) : host_(host) {}

        class ConstIterator {
            using HostIterator = Container::const_iterator;

        public:
            ConstIterator(HostIterator iter) : iter_(iter) {}
            const Vector4 &operator*() const;
            ConstIterator &operator++();
            ConstIterator operator++(int);
            bool operator==(ConstIterator other) const;
            bool operator!=(const ConstIterator other) const;

        private:
            HostIterator iter_;
        };

    public:
        ConstIterator begin() const;
        ConstIterator end() const;
        size_t size() const;
        const Vector4 &operator[](size_t index) const;

    private:
        const Container &host_;
    };

    Triangle(const Vertex &a, const Vertex &b, const Vertex &c);
    Triangle(const std::array<Vertex, 3> vertices);

    const std::array<Vertex, 3> &getYOrderedVertices() const;
    TrianglePositionsView getYOrderedVerticesPositions() const;

    static Triangle linearTransform(const Matrix4 &transformMatrix, const Triangle &triangle);

private:
    void reorderVertices();

    std::array<Vertex, 3> vertices_;
};

} // namespace Primitives
} // namespace ScratchRenderer

#endif // PRIMITIVES_H
