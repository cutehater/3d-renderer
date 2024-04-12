#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "global_usings.h"
#include <array>

namespace ScratchRenderer {
namespace Primitives {
class Vertex {
public:
    Vertex() = default;
    Vertex(const Vector3 &position, const Vector3 &normal,
           const Vector3 &color);

    static Vertex interpolateVertexInsideTriangle(const Triangle &triangle,
                                                  const Vector3 &position);

    bool operator==(const Vertex &other) const;
    bool operator!=(const Vertex &other) const;

    Vector3 getPosition() const;
    Vector3 getColor() const;

private:
    Vector3 position_ = ZeroVector3;
    Vector3 color_ = ZeroVector3;
};

class Ray {
public:
    Ray() = default;
    Ray(const Vector3 &origin, const Vector3 &direction);

    Vector3 getOrigin() const;
    Vector3 getDirection() const;

private:
    Vector3 origin_ = ZeroVector3;
    Vector3 direction_ = ZeroVector3;
};

class Triangle {
public:
    class TrianglePositionsView {
        using Container = const std::array<Vertex, 3>;

        friend class Triangle;
        TrianglePositionsView(Container *host) : host_(host) {}

        class ConstIterator {
            using HostIterator = Container::const_iterator;

        public:
            ConstIterator(HostIterator iter) : iter_(iter) {}

            Vector3 operator*() const { return iter_->getPosition(); }
            ConstIterator &operator++() {
                ++iter_;
                return *this;
            }
            bool operator==(const ConstIterator &other) const {
                return iter_ == other.iter_;
            }
            bool operator!=(const ConstIterator &other) const {
                return iter_ != other.iter_;
            }

        private:
            HostIterator iter_;
        };

    public:
        ConstIterator begin() const { return ConstIterator(host_->begin()); }
        ConstIterator end() const { return ConstIterator(host_->end()); }
        size_t size() const { return host_->size(); }
        Vector3 operator[](size_t index) const {
            return (*host_)[index].getPosition();
        }

    private:
        Container *host_;
    };

public:
    Triangle() = default;
    Triangle(const Vertex &a, const Vertex &b, const Vertex &c);

    const std::array<Vertex, 3> &getVertices() const;
    TrianglePositionsView getVerticesPositions() const;
    const std::array<double, 3> &
    getBarycentricCoordinates(const Vector3 &p) const;

private:
    std::array<Vertex, 3> vertices_;
};

class Plane {
public:
    Plane() = default;
    Plane(const Vector3 &a, const Vector3 &b, const Vector3 &c);
    Plane(const Vector3 &normal, double orientedDistFromOrigin);
    Plane(const Vector3 &normal, const Vector3 &p);
    Plane(const Triangle &triangle);

    Vector3 getNormal() const;
    double getOrientedDistFromOrigin() const;

private:
    Vector3 normal_ = ZeroVector3;
    double orientedDistFromOrigin_ = 0.0;
};
} // namespace Primitives
} // namespace ScratchRenderer

#endif // PRIMITIVES_H
