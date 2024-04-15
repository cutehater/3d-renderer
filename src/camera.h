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

    const std::vector<Primitives::Triangle> &
    projectWorldObjects(const World &world) const;

    void translate(const Vector4 &v);
    void rotate(const Matrix4 &m);

private:
    void buildTransformMatrix();
    Primitives::Triangle
    convertTriangleToCameraCoordinates(Primitives::Triangle triangle) const;
    bool isFront(const Vector4 &vertexPosition) const;
    std::optional<Primitives::Vertex>
    intersectEdgeNearPlane(Primitives::Triangle &triangle,
                           size_t vertexIdx) const;
    std::vector<Primitives::Triangle>
    clipTriangleNearPlane(Primitives::Triangle triangle) const;
    Primitives::Triangle projectTriangle(Primitives::Triangle triangle) const;

    Matrix4 rotation_matrix_;
    Matrix4 translation_matrix_;
    Matrix4 projection_matrix_;
};
} // namespace ScratchRenderer

#endif // CAMERA_H
