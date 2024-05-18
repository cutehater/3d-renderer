#include "vector4.h"
#include "glm/ext/scalar_relational.hpp"
#include <cassert>

namespace ScratchRenderer {

Vector4::Vector4() : glm::dvec4(0, 0, 0, 1) {}

Vector4::Vector4(double x, double y, double z) : glm::dvec4(x, y, z, 1) {}

Vector4::Vector4(const Vector3 &v) : glm::dvec4(v.x, v.y, v.z, 1) {}

Vector4::Vector4(const glm::dvec4 &v) : glm::dvec4(v.x, v.y, v.z, v.w) {
    assert(!glm::equal(w, 0.0, Epsilon) && "w-coordinate shouldn't be null");
    normalize();
}

Vector4 &Vector4::operator+=(const Vector4 &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vector4 &Vector4::operator-=(const Vector4 &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Vector4 &Vector4::operator*=(double k) {
    x *= k;
    y *= k;
    z *= k;
    return *this;
}

Vector4 &Vector4::operator/=(double k) {
    assert(!glm::equal(k, 0.0, Epsilon) && "vector division on zero");
    x /= k;
    y /= k;
    z /= k;
    return *this;
}

Vector4 operator+(const Vector4 &v, const Vector4 &u) { return Vector4(v.x + u.x, v.y + u.y, v.z + u.z); }

Vector4 operator-(const Vector4 &v, const Vector4 &u) { return Vector4(v.x - u.x, v.y - u.y, v.z - u.z); }

Vector4 operator*(const Vector4 &v, double k) { return Vector4(v.x * k, v.y * k, v.z * k); }

Vector4 operator/(const Vector4 &v, double k) {
    assert(!glm::equal(k, 0.0, Epsilon) && "vector division on zero");
    return v * (1.0 / k);
}

bool Vector4::operator==(const Vector4 &other) const {
    return glm::equal(x, other.x, Epsilon) && glm::equal(y, other.y, Epsilon) &&
           glm::equal(z, other.z, Epsilon);
}

bool Vector4::operator!=(const Vector4 &other) const { return !(*this == other); }

void Vector4::normalize() {
    x /= w;
    y /= w;
    z /= w;
    w = 1;
}

double Vector4::length() const { return std::sqrt(x * x + y * y + z * z); }

} // namespace ScratchRenderer
