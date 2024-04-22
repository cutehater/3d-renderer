#include "vector4.h"

#include "glm/ext/scalar_relational.hpp"

namespace ScratchRenderer {
Vector4::Vector4() : glm::dvec4(0, 0, 0, 1) {}

Vector4::Vector4(double x, double y, double z) : glm::dvec4(x, y, z, 1) {}

Vector4::Vector4(const Vector3 &v) : glm::dvec4(v.x, v.y, v.z, 1) {}

Vector4::Vector4(const glm::dvec4 &v) : glm::dvec4(v.x, v.y, v.z, v.w) {}

Vector4 operator+(const Vector4 &v, const Vector4 &u) {
    assert(!glm::equal(v.w * u.w, 0.0, Epsilon) && "w-coordinate shouldn't be null");
    return Vector4(v.x / v.w + u.x / u.w, v.y / v.w + u.y / u.w, v.z / v.w + u.z / u.w);
}

Vector4 operator-(const Vector4 &v, const Vector4 &u) {
    assert(!glm::equal(v.w * u.w, 0.0, Epsilon) && "w-coordinate shouldn't be null");
    return Vector4(v.x / v.w - u.x / u.w, v.y / v.w - u.y / u.w, v.z / v.w - u.z / u.w);
}

Vector4 operator*(const Vector4 &v, double k) {
    assert(!glm::equal(v.w, 0.0, Epsilon) && "w-coordinate shouldn't be null");
    return Vector4(v.x / v.w * k, v.y / v.w * k, v.z / v.w * k);
}

Vector4 operator/(const Vector4 &v, double k) {
    assert(!glm::equal(v.w, 0.0, Epsilon) && "w-coordinate shouldn't be null");
    return v * (1.0 / k);
}

Vector4 &Vector4::operator+=(const Vector4 &other) {
    *this = *this + other;
    return *this;
}

Vector4 &Vector4::operator-=(const Vector4 &other) {
    *this = *this - other;
    return *this;
}

Vector4 &Vector4::operator*=(double k) {
    *this = *this * k;
    return *this;
}

Vector4 &Vector4::operator/=(double k) {
    *this = *this / k;
    return *this;
}

bool Vector4::operator==(const Vector4 &other) const {
    assert(!glm::equal(this->w * other.w, 0.0, Epsilon) && "w-coordinate shouldn't be null");
    return glm::equal(this->x * other.w, this->w * other.x, Epsilon) &&
           glm::equal(this->y * other.w, this->w * other.y, Epsilon) &&
           glm::equal(this->z * other.w, this->w * other.z, Epsilon);
}

bool Vector4::operator!=(const Vector4 &other) const { return !(*this == other); }

void Vector4::normalize() {
    // assert(!glm::equal(this->w, 0.0, Epsilon) && "w-coordinate shouldn't be null");
    x /= w;
    y /= w;
    z /= w;
    w = 1;
}

double Vector4::length() const {
    // assert(!glm::equal(this->w, 0.0, Epsilon) && "w-coordinate shouldn't be null");
    return (x * x + y * y + z * z) / w * w;
}

} // namespace ScratchRenderer
