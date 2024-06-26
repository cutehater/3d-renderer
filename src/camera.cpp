#include "camera.h"

#include "configuration.h"
#include "glm/ext.hpp"

#include <array>
#include <cassert>

namespace ScratchRenderer {

Camera::Camera()
    : rotationMatrix_(IdentityMatrix), translationMatrix_(IdentityMatrix),
      projectionMatrix_(getProjectionMatrix()) {}

Matrix4 Camera::getProjectionMatrix() const {
    constexpr double a = configuration::gAspectRatio;
    constexpr double n = configuration::gNearPlaneDist;
    constexpr double f = configuration::gFarPlaneDist;
    constexpr double alpha = configuration::gFieldOfViewAngle;
    const double e = 1.0 / tan(alpha / 2);
    const double l = -n / e;
    const double r = n / e;
    const double b = -a * n / e;
    const double t = a * n / e;

    // glm matrices written by columns
    return Matrix4{{2 * n / (r - l), 0, 0, 0},
                   {0, 2 * n / (t - b), 0, 0},
                   {-(r + l) / (r - l), -(t + b) / (t - b), (f + n) / (f - n), 1},
                   {0, 0, -2 * n * f / (f - n), 0}};
}

std::vector<Primitives::Triangle> Camera::projectWorldObjects(const World &world) const {
    std::vector<Primitives::Triangle> projectedTriangles;
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

void Camera::translate(const Vector3 &axe, double length) {
    translationMatrix_ =
        glm::translate(translationMatrix_, Vector3(glm::transpose(rotationMatrix_) * Vector4(-axe) * length));
}

void Camera::rotate(const Vector3 &axe, double angle) {
    assert(!glm::equal(glm::length(axe), 0.0, Epsilon) &&
           "camera rotation vector should have positive length");
    rotationMatrix_ =
        glm::rotate(rotationMatrix_, angle, Vector3(glm::transpose(rotationMatrix_) * Vector4(axe)));
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
    return vertexPosition.z >= configuration::gNearPlaneDist;
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
        double backPlaneDist = configuration::gNearPlaneDist - verticesPositions[backIdx].z;
        if (backPlaneDist < Epsilon) {
            return Primitives::Vertex(Vector4(verticesPositions[backIdx].x, verticesPositions[backIdx].y,
                                              configuration::gNearPlaneDist),
                                      triangle.getYOrderedVertices()[backIdx].getColor());
        }
        double coef = backPlaneDist / direction.z;
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
                Primitives::Triangle(clippedVertices[0], clippedVertices[2], clippedVertices[3])};
    default:
        assert(false && "invalid number of vertices in clipping");
    }
}

Primitives::Triangle Camera::projectTriangle(const Primitives::Triangle &triangle) const {
    std::array<Primitives::Vertex, 3> projectedVertices;

    for (size_t i = 0; i < 3; ++i) {
        Vector4 projectedVertexPosition = projectionMatrix_ * triangle.getYOrderedVerticesPositions()[i];
        projectedVertices[i] =
            Primitives::Vertex(projectedVertexPosition, triangle.getYOrderedVertices()[i].getColor());
    }

    return Primitives::Triangle(projectedVertices);
}
} // namespace ScratchRenderer
