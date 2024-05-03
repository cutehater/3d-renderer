#ifndef CAMERA_H
#define CAMERA_H

#include "global_usings.h"
#include "primitives.h"
#include "world.h"

#include <optional>
#include <vector>

namespace ScratchRenderer {
class Camera {
public:
    Camera();

    std::vector<Primitives::Triangle> projectWorldObjects(const World &world) const;

    void translate(const Vector3 &axe, double length);
    void rotate(const Vector3 &axe, double angle);

private:
    Primitives::Triangle convertTriangleToCameraCoordinates(const Primitives::Triangle &triangle) const;
    bool isFront(const Vector4 &vertexPosition) const;
    std::optional<Primitives::Vertex> intersectEdgeNearPlane(const Primitives::Triangle &triangle,
                                                             size_t vertexIdx) const;
    std::vector<Primitives::Triangle> clipTriangleNearPlane(const Primitives::Triangle &triangle) const;
    Primitives::Triangle projectTriangle(const Primitives::Triangle &triangle) const;
    void buildProjectionMatrix();

    Matrix4 rotationMatrix_;
    Matrix4 translationMatrix_;
    Matrix4 projectionMatrix_;
};
} // namespace ScratchRenderer

#endif // CAMERA_H
