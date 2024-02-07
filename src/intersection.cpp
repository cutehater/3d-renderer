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

    if (glm::equal(numerator, 0.0, glm::epsilon<double>())) {
        return Intersection{Intersection::Type::Coincide,
                            ray.getOrigin()}; // ray lies on plane
    } else if (glm::equal(denominator, 0.0, glm::epsilon<double>())) {
        return Intersection{
            Intersection::Type::NonIntersect}; // ray is parallel to plane
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
        std::vector<glm::dvec3> vertices = triangle.getVerticesPositions();
        for (auto &v : vertices) {
            v -= intersection.point;
        }

        std::vector<glm::dvec3> crossProducts(vertices.size());
        for (size_t i = 0; i < vertices.size(); ++i) {
            crossProducts[i] =
                glm::cross(vertices[i], vertices[(i + 1) % vertices.size()]);
        }

        if (glm::dot(crossProducts[0], crossProducts[1]) <
                -glm::epsilon<double>() ||
            glm::dot(crossProducts[0], crossProducts[2]) <
                -glm::epsilon<double>()) {
            intersection.type = Intersection::Type::NonIntersect;
        }
    }

    return intersection;
}

Primitives::Vertex createClippedVertex(const Primitives::Vertex &front,
                                       const Primitives::Vertex &back,
                                       const Primitives::Plane &plane) {
    Primitives::Ray ray(glm::dvec3(front.getPosition()),
                        glm::normalize(glm::dvec3(back.getPosition()) -
                                       glm::dvec3(front.getPosition())));
    glm::dvec3 pos = intersectRayPlane(ray, plane).point;
    glm::dvec4 pos4 = glm::dvec4(pos.x, pos.y, pos.z, 1.0);

    double relationFactor = (front.getPosition() - pos4).length() /
                            (front.getPosition() - back.getPosition()).length();
    return Primitives::Vertex(pos4,
                              front.getNorm() * relationFactor +
                                  back.getNorm() * (1 - relationFactor),
                              front.getTexture() * relationFactor +
                                  back.getTexture() * (1 - relationFactor),
                              front.getColor() * relationFactor +
                                  back.getColor() * (1 - relationFactor));
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
        double intersection =
            glm::dot(plane.getNorm(), vertex) - plane.getDistFromOrigin();
        if (intersection > glm::epsilon<double>()) {
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

        newVertices.push_back(createClippedVertex(
            triangleVertices[frontIdx], triangleVertices[backIdx], plane));
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