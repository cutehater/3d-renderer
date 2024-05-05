#include "primitives.h"
#include "gtest/gtest.h"

using namespace ScratchRenderer;
using Vertex = Primitives::Vertex;
using Triangle = Primitives::Triangle;

TEST(TriangleTest, GetYOrderedVertices) {
    Vertex a(Vector4(1.0, 4.0, 1.0));
    Vertex b(Vector4(2.0, 3.0, 2.0));
    Vertex c(Vector4(3.0, 2.0, 3.0));
    Triangle triangle(a, b, c);
    auto vertices = triangle.getYOrderedVertices();

    EXPECT_EQ(vertices[0], c);
    EXPECT_EQ(vertices[1], b);
    EXPECT_EQ(vertices[2], a);
}

TEST(TriangleTest, GetYOrderedVerticesPositions) {
    Vertex a(Vector4(1.0, 3.0, 1.0));
    Vertex b(Vector4(2.0, 2.0, 2.0));
    Vertex c(Vector4(3.0, 4.0, 3.0));
    Triangle triangle(a, b, c);
    auto verticesPositions = triangle.getYOrderedVerticesPositions();

    EXPECT_EQ(verticesPositions.size(), 3);
    EXPECT_EQ(verticesPositions[0], b.getPosition());
    EXPECT_EQ(verticesPositions[1], a.getPosition());
    EXPECT_EQ(verticesPositions[2], c.getPosition());

    ASSERT_DEATH(verticesPositions[3], ".*");
}

TEST(TriangleTest, LinearTransform) {
    // glm matrices written by columns
    Matrix4 transformMatrix = {
        {1, 0, 1, 0},
        {2, 3, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 1},
    };

    Vertex a(Vector4(1.0, 2.0, 3.0));
    Vertex b(Vector4(2.0, 3.0, 4.0));
    Vertex c(Vector4(3.0, 4.0, 5.0));
    Triangle triangle(a, b, c);
    Triangle transformedTriangle = Triangle::linearTransform(transformMatrix, triangle);
    auto verticesPositions = transformedTriangle.getYOrderedVerticesPositions();

    EXPECT_EQ(verticesPositions[0], Vector4(5.0, 6.0, 7.0));
    EXPECT_EQ(verticesPositions[1], Vector4(8.0, 9.0, 10.0));
    EXPECT_EQ(verticesPositions[2], Vector4(11.0, 12.0, 13.0));
}
