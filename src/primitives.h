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

    static Vertex interpolate(const Vertex &a, const Vertex &b, double coef);

    bool operator==(const Vertex &other) const;
    bool operator!=(const Vertex &other) const;

    Vector4 &getPosition();
    Color &getColor();

private:
    Vector4 position_ = ZeroVector4;
    Color color_ = sf::Color::Black;
};

class Triangle {
public:
    class TrianglePositionsRef {
        using Container = std::array<Vertex, 3>;

        friend class Triangle;
        TrianglePositionsRef(Container *host) : host_(host) {}

        class Iterator {
            using HostIterator = Container::iterator;

        public:
            Iterator(HostIterator iter) : iter_(iter) {}
            Vector4 &operator*();
            Iterator &operator++();
            Iterator operator++(int);
            bool operator==(Iterator other) const;
            bool operator!=(const Iterator other) const;

        private:
            HostIterator iter_;
        };

    public:
        Iterator begin() const;
        Iterator end() const;
        size_t size() const;
        Vector4 &operator[](size_t index) const;

    private:
        Container *host_;
    };

public:
    Triangle() = default;
    Triangle(const Vertex &a, const Vertex &b, const Vertex &c);

    const std::array<Vertex, 3> &getVertices() const;
    TrianglePositionsRef getVerticesPositions();

private:
    std::array<Vertex, 3> vertices_;
};

} // namespace Primitives
} // namespace ScratchRenderer

#endif // PRIMITIVES_H
