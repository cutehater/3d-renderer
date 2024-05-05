#include "primitives.h"
#include "gtest/gtest.h"

using namespace ScratchRenderer;
using Vertex = Primitives::Vertex;

TEST(VertexTest, ConstructorWithPosition) {
    Vector4 position(1.0, 2.0, 3.0);
    Vertex vertex(position);

    EXPECT_EQ(vertex.getPosition(), position);
}

TEST(VertexTest, ConstructorWithPositionAndColor) {
    Vector4 position(1.0, 2.0, 3.0);
    Color color(255, 0, 0);
    Vertex vertex(position, color);

    EXPECT_EQ(vertex.getPosition(), position);
    EXPECT_EQ(vertex.getColor(), color);
}

TEST(VertexTest, Equality) {
    Vector4 position1(1.0, 2.0, 3.0);
    Vector4 position2(1.0, 2.0, 3.1);
    Color color1(255, 0, 0);
    Color color2(0, 0, 255);
    Vertex vertex1(position1, color1);
    Vertex vertex2(position1, color2);
    Vertex vertex3(position2, color1);

    EXPECT_TRUE(vertex1 == vertex2);
    EXPECT_TRUE(vertex1 != vertex3);
}

TEST(VertexTest, MatrixMultiplication) {
    Vector4 position(1.0, 2.0, 3.0);
    Color color(255, 0, 0);
    Vertex vertex(position, color);

    // glm matrices written by columns
    Matrix4 m = {
        {1, 0, 1, 0},
        {2, 3, 1, 0},
        {0, 0, 1, 1},
        {0, 0, 1, 0},
    };
    Vertex result = m * vertex;
    Vector4 newPosition(glm::dvec4(5.0, 6.0, 7.0, 3.0));

    EXPECT_EQ(result.getPosition(), newPosition);
    EXPECT_EQ(result.getColor(), color);
}

TEST(VertexTest, Interpolate) {
    Vector4 position1(1.0, 2.0, 3.0);
    Vector4 position2(4.0, 5.0, 6.0);
    Color color1(255, 0, 0, 0);
    Color color2(0, 255, 0, 0);
    Vertex vertex1(position1, color1);
    Vertex vertex2(position2, color2);
    double coef = 0.5;
    Vertex result = Vertex::interpolate(vertex1, vertex2, coef);

    EXPECT_EQ(result.getPosition(), Vector4(2.5, 3.5, 4.5));
    EXPECT_EQ(result.getColor(), Color(127, 127, 0, 0));

    ASSERT_DEATH(Vertex::interpolate(vertex1, vertex2, -1), ".*");
    ASSERT_DEATH(Vertex::interpolate(vertex1, vertex2, 1.1), ".*");
}
