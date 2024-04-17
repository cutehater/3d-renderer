#include "camera.h"

#include "configuration.h"
#include "glm/ext.hpp"
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
    const Primitives::Triangle &triangle) const {
    std::array<Primitives::Vertex, 3> convertedVertices;

    for (size_t i = 0; i < 3; ++i) {
        Vector4 convertedVertexPosition =
            glm::transpose(rotation_matrix_) * translation_matrix_ *
            triangle.getYOrderedVerticesPositions()[i];
        convertedVertexPosition.normalize();
        convertedVertices[i] =
            Primitives::Vertex(convertedVertexPosition,
                               triangle.getYOrderedVertices()[i].getColor());
    }

    return Primitives::Triangle(convertedVertices);
}

bool Camera::isFront(const Vector4 &vertexPosition) const {
    return (vertexPosition.z - configuration::kNearPlaneDist) > Epsilon;
};

std::optional<Primitives::Vertex>
Camera::intersectEdgeNearPlane(const Primitives::Triangle &triangle,
                               size_t vertexIdx) const {
    auto verticesPositions = triangle.getYOrderedVerticesPositions();
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
        return Primitives::Vertex::interpolate(
            triangle.getYOrderedVertices()[backIdx],
            triangle.getYOrderedVertices()[frontIdx], coef);
    } else {
        return std::nullopt;
    }
}

std::vector<Primitives::Triangle>
Camera::clipTriangleNearPlane(const Primitives::Triangle &triangle) const {
    std::vector<Primitives::Vertex> clippedVertices;
    clippedVertices.reserve(4);
    for (size_t idx = 0; idx < 3; ++idx) {
        if (isFront(triangle.getYOrderedVerticesPositions()[idx])) {
            clippedVertices.emplace_back(triangle.getYOrderedVertices()[idx]);
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
Camera::projectTriangle(const Primitives::Triangle &triangle) const {
    std::array<Primitives::Vertex, 3> projectedVertices;

    for (size_t i = 0; i < 3; ++i) {
        Vector4 projectedVertexPosition =
            projection_matrix_ * triangle.getYOrderedVerticesPositions()[i];
        projectedVertexPosition.normalize();
        assert(projectedVertexPosition.x >= -1 - Epsilon &&
               projectedVertexPosition.x <= 1 + Epsilon &&
               projectedVertexPosition.y >= -1 - Epsilon &&
               projectedVertexPosition.y <= 1 + Epsilon &&
               projectedVertexPosition.z >= -1 - Epsilon &&
               projectedVertexPosition.z <= 1 + Epsilon &&
               projectedVertexPosition.w > -Epsilon &&
               "Invalid canonical vertex transform");
        projectedVertices[i] =
            Primitives::Vertex(projectedVertexPosition,
                               triangle.getYOrderedVertices()[i].getColor());
    }
}

void Camera::rotate(const Vector3 &axe, double angle) {
    rotation_matrix_ = glm::rotate(rotation_matrix_, angle, axe);
}

void Camera::translate(const Vector3 &axe, double length) {
    translation_matrix_ = glm::translate(translation_matrix_, axe * length);
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
