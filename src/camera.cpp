#include "camera.h"

#include "configuration.h"
#include "glm/ext.hpp"
#include <array>
#include <iostream>
#include <optional>

namespace ScratchRenderer {

Camera::Camera() : rotationMatrix_(IdentityMatrix), translationMatrix_(IdentityMatrix) {
    buildTransformMatrix();
}

std::vector<Primitives::Triangle> Camera::projectWorldObjects(const World &world) const {
    std::vector<Primitives::Triangle> projectedTriangles;
    // all triangles will be clipped into two in worst case
    projectedTriangles.reserve(2 * world.size());

    for (const Primitives::Triangle &triangle : world) {
        Primitives::Triangle projectedTriangle = convertTriangleToCameraCoordinates(triangle);
        std::vector<Primitives::Triangle> clippedTriangles = clipTriangleNearPlane(projectedTriangle);
        for (Primitives::Triangle &clippedTriangle : clippedTriangles) {
            projectedTriangles.emplace_back(projectTriangle(clippedTriangle));
        }
    }

    return projectedTriangles;
}

Primitives::Triangle Camera::convertTriangleToCameraCoordinates(const Primitives::Triangle &triangle) const {
    std::array<Primitives::Vertex, 3> convertedVertices;

    for (size_t i = 0; i < 3; ++i) {
        Vector4 convertedVertexPosition =
            rotationMatrix_ * translationMatrix_ * triangle.getYOrderedVerticesPositions()[i];
        convertedVertices[i] =
            Primitives::Vertex(convertedVertexPosition, triangle.getYOrderedVertices()[i].getColor());
    }

    return Primitives::Triangle(convertedVertices);
}

bool Camera::isFront(const Vector4 &vertexPosition) const {
    return vertexPosition.z > configuration::kNearPlaneDist;
};

std::optional<Primitives::Vertex> Camera::intersectEdgeNearPlane(const Primitives::Triangle &triangle,
                                                                 size_t vertexIdx) const {
    auto verticesPositions = triangle.getYOrderedVerticesPositions();
    size_t frontIdx = vertexIdx;
    size_t backIdx = (vertexIdx + 1) % 3;
    if (!isFront(verticesPositions[frontIdx])) {
        std::swap(frontIdx, backIdx);
    }
    if (isFront(verticesPositions[frontIdx]) && !isFront(verticesPositions[backIdx])) {
        Vector4 direction = verticesPositions[frontIdx] - verticesPositions[backIdx];
        double backPlaneDist = configuration::kNearPlaneDist - verticesPositions[backIdx].z;
        if (backPlaneDist < Epsilon) {
            return Primitives::Vertex(Vector4(verticesPositions[backIdx].x, verticesPositions[backIdx].y,
                                              configuration::kNearPlaneDist),
                                      triangle.getYOrderedVertices()[backIdx].getColor());
        }
        Vector4 edgePlaneIntersection = verticesPositions[backIdx] + direction * backPlaneDist / direction.z;
        double coef = (edgePlaneIntersection - verticesPositions[backIdx]).length() / direction.length();
        return Primitives::Vertex::interpolate(triangle.getYOrderedVertices()[backIdx],
                                               triangle.getYOrderedVertices()[frontIdx], coef);
    } else {
        return std::nullopt;
    }
}

std::vector<Primitives::Triangle> Camera::clipTriangleNearPlane(const Primitives::Triangle &triangle) const {
    std::vector<Primitives::Vertex> clippedVertices;
    clippedVertices.reserve(4);
    for (size_t idx = 0; idx < 3; ++idx) {
        if (isFront(triangle.getYOrderedVerticesPositions()[idx])) {
            clippedVertices.emplace_back(triangle.getYOrderedVertices()[idx]);
        }
        std::optional<Primitives::Vertex> clippedVertex = intersectEdgeNearPlane(triangle, idx);
        if (clippedVertex.has_value()) {
            clippedVertices.emplace_back(std::move(clippedVertex.value()));
        }
    }

    switch (clippedVertices.size()) {
    case 0:
        return {};
    case 3:
        return {Primitives::Triangle(clippedVertices[0], clippedVertices[1], clippedVertices[2])};
    case 4:
        return {Primitives::Triangle(clippedVertices[0], clippedVertices[1], clippedVertices[2]),
                Primitives::Triangle(clippedVertices[1], clippedVertices[2], clippedVertices[3])};
    default:
        assert(false && "Invalid number of vertices in clipping");
    }
}

Primitives::Triangle Camera::projectTriangle(const Primitives::Triangle &triangle) const {
    std::array<Primitives::Vertex, 3> projectedVertices;

    for (size_t i = 0; i < 3; ++i) {
        Vector4 projectedVertexPosition = projectionMatrix_ * triangle.getYOrderedVerticesPositions()[i];
        projectedVertexPosition.normalize();
        projectedVertices[i] =
            Primitives::Vertex(projectedVertexPosition, triangle.getYOrderedVertices()[i].getColor());
    }

    return Primitives::Triangle(projectedVertices);
}

void Camera::rotate(const Vector3 &axe, double angle) {
    rotationMatrix_ =
        glm::rotate(rotationMatrix_, angle, Vector3(glm::transpose(rotationMatrix_) * Vector4(axe)));
}

void Camera::translate(const Vector3 &axe, double length) {
    translationMatrix_ =
        glm::translate(translationMatrix_, Vector3(glm::transpose(rotationMatrix_) * Vector4(-axe) * length));
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

    projectionMatrix_ = Matrix4{{2 * n / (r - l), 0, 2 * (r + l) / (r - l), 0},
                                {0, 2 * n / (b - t), 0, 0},
                                {0, 0, 0, -2 * n * f / (f - n)},
                                {0, 0, 1, 0}};
}
} // namespace ScratchRenderer
