#include "camera.h"

#include "configuration.h"
#include "glm/ext/scalar_relational.hpp"
#include <array>
#include <optional>
#include <trigonometric.hpp>

namespace ScratchRenderer {

Camera::Camera()
    : rotation_matrix_(IdentityMatrix), translation_matrix_(IdentityMatrix) {
    buildTransformMatrix();
}

const std::vector<Primitives::Triangle> &
Camera::projectWorldObjects(const World &world) const {
    std::vector<Primitives::Triangle> projectedTriangles;
    // all triangles will be clipped into two in worst case
    projectedTriangles.reserve(2 * world.size());

    for (const Primitives::Triangle &triangle : world) {
        Primitives::Triangle projectedTriangle =
            convertTriangleToCameraCoordinates(triangle);
        std::vector<Primitives::Triangle> clippedTriangles =
            clipTriangleNearPlane(projectedTriangle);
        for (Primitives::Triangle &clippedTriangle : clippedTriangles) {
            projectedTriangles.emplace_back(projectTriangle(clippedTriangle));
        }
    }

    return projectedTriangles;
}

Primitives::Triangle Camera::convertTriangleToCameraCoordinates(
    Primitives::Triangle triangle) const {
    for (Vector4 &vertexPosition : triangle.getVerticesPositions()) {
        vertexPosition = glm::transpose(rotation_matrix_) *
                         translation_matrix_ * vertexPosition;
        vertexPosition.normalize();
    }
    return triangle;
}

bool Camera::isFront(const Vector4 &vertexPosition) const {
    return (vertexPosition.z - configuration::kNearPlaneDist) > Epsilon;
};

std::optional<Primitives::Vertex>
Camera::intersectEdgeNearPlane(Primitives::Triangle &triangle,
                               size_t vertexIdx) const {
    auto verticesPositions = triangle.getVerticesPositions();
    size_t frontIdx = vertexIdx;
    size_t backIdx = (vertexIdx + 1) % 3;
    if (!isFront(verticesPositions[frontIdx])) {
        std::swap(frontIdx, backIdx);
    }
    if (!isFront(verticesPositions[backIdx])) {
        Vector4 direction =
            verticesPositions[frontIdx] - verticesPositions[backIdx];
        double backPlaneDist =
            configuration::kNearPlaneDist - verticesPositions[backIdx].z;
        Vector4 edgePlaneIntersection = verticesPositions[backIdx] +
                                        direction * backPlaneDist / direction.z;
        double coef =
            (edgePlaneIntersection - verticesPositions[backIdx]).length() /
            direction.length();
        return Primitives::Vertex::interpolate(triangle.getVertices()[backIdx],
                                               triangle.getVertices()[frontIdx],
                                               coef);
    } else {
        return std::nullopt;
    }
}

std::vector<Primitives::Triangle>
Camera::clipTriangleNearPlane(Primitives::Triangle triangle) const {
    std::vector<Primitives::Vertex> clippedVertices;
    clippedVertices.reserve(4);
    for (size_t idx = 0; idx < 3; ++idx) {
        if (isFront(triangle.getVerticesPositions()[idx])) {
            clippedVertices.emplace_back(triangle.getVertices()[idx]);
        }
        std::optional<Primitives::Vertex> clippedVertex =
            intersectEdgeNearPlane(triangle, idx);
        if (clippedVertex) {
            clippedVertices.emplace_back(std::move(clippedVertex));
        }
    }

    switch (clippedVertices.size()) {
    case 0:
        return {};
    case 3:
        return {triangle};
    case 4:
        return {Primitives::Triangle(clippedVertices[0], clippedVertices[1],
                                     clippedVertices[2]),
                Primitives::Triangle(clippedVertices[1], clippedVertices[2],
                                     clippedVertices[3])};
    default:
        assert(false && "Invalid number of vertices in clipping");
    }
}

Primitives::Triangle
Camera::projectTriangle(Primitives::Triangle triangle) const {
    for (Vector4 &vertexPosition : triangle.getVerticesPositions()) {
        vertexPosition = projection_matrix_ * vertexPosition;
        vertexPosition.normalize();
        assert(vertexPosition.x >= -1 - Epsilon &&
               vertexPosition.x <= 1 + Epsilon &&
               vertexPosition.y >= -1 - Epsilon &&
               vertexPosition.y <= 1 + Epsilon &&
               vertexPosition.z >= -1 - Epsilon &&
               vertexPosition.z <= 1 + Epsilon && vertexPosition.w > -Epsilon &&
               "Invalid canonical vertex transform");
    }
}

void Camera::rotate(const Matrix4 &m) { rotation_matrix_ *= m; }

void Camera::translate(const Vector4 &v) {
    Vector3 shift = Vector4(rotation_matrix_ * v).convertTo3DVector();
    translation_matrix_[0][3] = shift.x;
    translation_matrix_[1][3] = shift.y;
    translation_matrix_[2][3] = shift.z;
}

void Camera::buildTransformMatrix() {
    constexpr double a = configuration::kAspectRatio;
    constexpr double n = configuration::kNearPlaneDist;
    constexpr double f = configuration::kFarPlaneDist;
    constexpr double alpha = configuration::kFieldOfViewAngle;
    const double e = 1.0 / tan(alpha / 2);
    const double l = -n / e;
    const double r = n / e;
    const double b = -a * n / e;
    const double t = a * n / e;

    projection_matrix_ = Matrix4{{2 * n / (r - l), 0, (r + l) / (r - l), 0},
                                 {0, 2 * n / (t - b), (t + b) / (t - b), 0},
                                 {0, 0, n + f / (n - f), 2 * n * f / (n - f)},
                                 {0, 0, -1, 0}};
}
} // namespace ScratchRenderer
