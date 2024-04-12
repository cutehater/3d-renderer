#include "clipping.h"

#include "glm/geometric.hpp"
#include "intersection.h"
#include <algorithm>

namespace ScratchRenderer {
enum class VertexType { Front, Back };

const std::array<VertexType, 3> &getTriangleVerticesRelationToPlane(
    const std::array<Primitives::Vertex, 3> &triangleVertices,
    Primitives::Triangle::TrianglePositionsView triangleVerticesPositions,
    const Primitives::Plane &plane) {
    std::array<VertexType, 3> verticesTypes;

    for (size_t i = 0; i < triangleVerticesPositions.size(); ++i) {
        Vector3 vertex = triangleVerticesPositions[i];
        double orientedDist = glm::dot(plane.getNormal(), vertex) -
                              plane.getOrientedDistFromOrigin();
        if (orientedDist > Epsilon) {
            verticesTypes[i] = VertexType::Front;
        } else {
            verticesTypes[i] = VertexType::Back;
        }
    }

    return verticesTypes;
}

Intersection intersectTriangleEdgePlane(
    const std::array<Primitives::Vertex, 3> &triangleVertices,
    Primitives::Triangle::TrianglePositionsView triangleVerticesPositions,
    const std::array<VertexType, 3> &verticesTypes, size_t vertexIndex,
    const Primitives::Plane &plane) {
    size_t frontIdx = vertexIndex;
    size_t backIdx = (vertexIndex + 1) % triangleVerticesPositions.size();
    if (verticesTypes[frontIdx] == verticesTypes[backIdx]) {
        return Intersection{Intersection::Type::NonIntersect};
    }
    if (verticesTypes[frontIdx] != VertexType::Front) {
        std::swap(frontIdx, backIdx);
    }

    Primitives::Ray intersectionRay(
        Vector3(triangleVertices[frontIdx].getPosition()),
        glm::normalize(triangleVertices[backIdx].getPosition() -
                       triangleVertices[frontIdx].getPosition()));
    return intersectRayPlane(intersectionRay, plane);
}

const ClippedTriangle &clipPlaneTriangle(const Primitives::Triangle &triangle,
                                         const Primitives::Plane &plane) {
    auto triangleVertices = triangle.getVertices();
    auto triangleVerticesPositions = triangle.getVerticesPositions();
    std::array<VertexType, 3> verticesTypes =
        getTriangleVerticesRelationToPlane(triangleVertices,
                                           triangleVerticesPositions, plane);

    {
        int frontVerticesNum = std::count_if(
            verticesTypes.begin(), verticesTypes.end(),
            [](const VertexType &v) { return v == VertexType::Front; });
        if (frontVerticesNum == 0) {
            return ClippedTriangle{ClippedTriangle::Type::Empty};
        } else if (frontVerticesNum == 3) {
            return ClippedTriangle{ClippedTriangle::Type::OneTriangle,
                                   {triangle}};
        }
    }

    size_t clippingVertexCnt = 0;
    std::array<Primitives::Vertex, 4> newVertices;

    {
        for (size_t i = 0; i < triangleVertices.size(); ++i) {
            if (verticesTypes[i] == VertexType::Front) {
                assert(clippingVertexCnt < 4 &&
                       "Triangle clipping can't contain more than 4 vertices");
                newVertices[clippingVertexCnt++] = triangleVertices[i];
            }

            auto intersection = intersectTriangleEdgePlane(
                triangleVertices, triangleVerticesPositions, verticesTypes, i,
                plane);
            assert(intersection.type != Intersection::Type::Coincide &&
                   "Ray shouldn't lie on plane while clipping triangle edges");
            if (intersection.type == Intersection::Type::Intersect) {
                assert(clippingVertexCnt < 4 &&
                       "Triangle clipping can't contain more than 4 vertices");
                newVertices[clippingVertexCnt++] =
                    Primitives::Vertex::interpolateVertexInsideTriangle(
                        triangle, intersection.point);
            }
        }
    }

    if (clippingVertexCnt == 3) {
        return ClippedTriangle{
            ClippedTriangle::Type::OneTriangle,
            {Primitives::Triangle(newVertices[0], newVertices[1],
                                  newVertices[2])}};
    } else {
        return ClippedTriangle{
            ClippedTriangle::Type::TwoTriangles,
            {Primitives::Triangle(newVertices[0], newVertices[1],
                                  newVertices[2]),
             Primitives::Triangle(newVertices[1], newVertices[2],
                                  newVertices[3])}};
    }
}

} // namespace ScratchRenderer
