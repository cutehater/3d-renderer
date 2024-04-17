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
    class Axe {
    public:
        static constexpr Vector3 X = Vector3(1, 0, 0);
        static constexpr Vector3 Y = Vector3(0, 1, 0);
        static constexpr Vector3 Z = Vector3(0, 0, 1);
    };

    Camera();

    const std::vector<Primitives::Triangle> &
    projectWorldObjects(const World &world) const;

    void translate(const Vector3 &axe, double length);
    void rotate(const Vector3 &axe, double angle);

private:
    void buildTransformMatrix();
    Primitives::Triangle convertTriangleToCameraCoordinates(
        const Primitives::Triangle &triangle) const;
    bool isFront(const Vector4 &vertexPosition) const;
    std::optional<Primitives::Vertex>
    intersectEdgeNearPlane(const Primitives::Triangle &triangle,
                           size_t vertexIdx) const;
    std::vector<Primitives::Triangle>
    clipTriangleNearPlane(const Primitives::Triangle &triangle) const;
    Primitives::Triangle
    projectTriangle(const Primitives::Triangle &triangle) const;

    Matrix4 rotation_matrix_;
    Matrix4 translation_matrix_;
    Matrix4 projection_matrix_;
};
} // namespace ScratchRenderer

#endif // CAMERA_H
