#ifndef VECTOR4_H
#define VECTOR4_H

#include "glm/ext/vector_double4.hpp"
#include "global_usings.h"

// 3d point (x, y, z) -> 4d point (x, y, z, 1)
// 4d point (x, y, z, w) -> 3d point (x / w, y / w, z / w)

namespace ScratchRenderer {
class Vector4 : public glm::dvec4 {
public:
    Vector4();
    Vector4(double x, double y, double z);
    Vector4(const glm::dvec4 &v);

    friend Vector4 operator+(const Vector4 &v, const Vector4 &u);
    friend Vector4 operator-(const Vector4 &v, const Vector4 &u);
    friend Vector4 operator*(const Vector4 &v, double k);
    friend Vector4 operator/(const Vector4 &v, double k);

    Vector4 &operator+=(const Vector4 &other);
    Vector4 &operator-=(const Vector4 &other);
    Vector4 &operator*=(double k);
    Vector4 &operator/=(double k);

    bool operator==(const Vector4 &other) const;
    bool operator!=(const Vector4 &other) const;

    void normalize();
    double length() const;
};

} // namespace ScratchRenderer

#endif // VECTOR4_H
