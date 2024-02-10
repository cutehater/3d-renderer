#include "intersection.h"

#include "glm/common.hpp"
#include "glm/ext/scalar_constants.hpp"
#include "glm/ext/scalar_relational.hpp"
#include <algorithm>

namespace ScratchRenderer {

Intersection intersectRayPlane(const Primitives::Ray &ray,
                               const Primitives::Plane &plane) {
    double numerator =
        glm::dot(plane.getNorm(), ray.getOrigin()) - plane.getDistFromOrigin();
    double denominator = glm::dot(plane.getNorm(), ray.getDirection());

    if (glm::equal(denominator, 0.0, glm::epsilon<double>())) {
        if (glm::equal(numerator, 0.0, glm::epsilon<double>())) {
            return Intersection{Intersection::Type::Coincide,
                                ray.getOrigin()}; // ray lies on plane
        } else {
            return Intersection{
                Intersection::Type::NonIntersect}; // ray is parallel to plane
        }
    } else {
        double fraction = -numerator / denominator;
        if (fraction < 0.0) {
            return Intersection{Intersection::Type::NonIntersect};
        } else {
            return Intersection{Intersection::Type::Intersect,
                                ray.getOrigin() +
                                    ray.getDirection() * fraction};
        }
    }
}

Intersection intersectRayTriangle(const Primitives::Ray &ray,
                                  const Primitives::Triangle &triangle) {
    Intersection intersection =
        intersectRayPlane(ray, Primitives::Plane(triangle));

    if (intersection.type != Intersection::Type::NonIntersect) {
        // checking if intersection lie inside triangle
        std::vector<double> vertices =
            triangle.getBarycentricWeights(intersection.point);
        if (vertices[0] < -glm::epsilon<double>() ||
            vertices[1] < -glm::epsilon<double>() ||
            vertices[2] < -glm::epsilon<double>()) {
            return Intersection{Intersection::Type::NonIntersect};
        }
    }

    return intersection;
}

std::vector<Primitives::Triangle>
intersectPlaneTriangle(const Primitives::Triangle &triangle,
                       const Primitives::Plane &plane) {
    enum class VertexType { Front, Back };
    int frontVerticesNum = 0;
    std::vector<Primitives::Vertex> triangleVertices = triangle.getVertices();
    std::vector<glm::dvec3> triangleVerticesPos =
        triangle.getVerticesPositions();
    std::vector<VertexType> verticesType(triangleVerticesPos.size());

    // determine vertices relation to plane
    for (size_t i = 0; i < triangleVerticesPos.size(); ++i) {
        glm::dvec3 vertex = triangleVerticesPos[i];
        double orientedDist =
            glm::dot(plane.getNorm(), vertex) - plane.getDistFromOrigin();
        if (orientedDist > glm::epsilon<double>()) {
            frontVerticesNum++;
            verticesType[i] = VertexType::Front;
        } else {
            verticesType[i] = VertexType::Back;
        }
    }

    if (frontVerticesNum == 0) { // triangle is hidden
        return {};
    } else if (frontVerticesNum == 3) { // triangle is fully visible
        return {triangle};
    }

    std::vector<Primitives::Vertex> newVertices;
    for (size_t i = 0; i < triangleVerticesPos.size(); ++i) {
        if (verticesType[i] == VertexType::Front) {
            newVertices.push_back(triangleVertices[i]);
        }

        size_t frontIdx = i, backIdx = (i + 1) % triangleVerticesPos.size();
        if (verticesType[frontIdx] == verticesType[backIdx]) {
            continue;
        }
        if (verticesType[frontIdx] != VertexType::Front) {
            std::swap(frontIdx, backIdx);
        }

        Primitives::Ray ray(
            glm::dvec3(triangleVertices[frontIdx].getPosition()),
            glm::normalize(
                glm::dvec3(triangleVertices[backIdx].getPosition()) -
                glm::dvec3(triangleVertices[frontIdx].getPosition())));
        glm::dvec3 intersection = intersectRayPlane(ray, plane).point;
        newVertices.push_back(Primitives::Vertex(
            triangle,
            glm::dvec4(intersection.x, intersection.y, intersection.z, 1.0)));
    }

    if (newVertices.size() == 3) {
        return {Primitives::Triangle(newVertices[0], newVertices[1],
                                     newVertices[2])};
    } else {
        return {Primitives::Triangle(newVertices[0], newVertices[1],
                                     newVertices[2]),
                Primitives::Triangle(newVertices[1], newVertices[2],
                                     newVertices[3])};
    }
}
} // namespace ScratchRenderer