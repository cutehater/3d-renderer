#include "object.h"
#include "gtest/gtest.h"

#include <numbers>
#include <vector>

using namespace ScratchRenderer;
using Triangle = Primitives::Triangle;
using Vertex = Primitives::Vertex;

std::vector<Triangle> makeObjectTriangles() {
    Triangle triangle1(Vertex(Vector4(1.0, 0.0, 0.0)), Vertex(Vector4(0.0, 1.0, 0.0)),
                       Vertex(Vector4(0.0, 0.0, 1.0)));
    Triangle triangle2(Vertex(Vector4(-1.0, 0.0, -1.0)), Vertex(Vector4(0.0, -1.0, 2.0)),
                       Vertex(Vector4(3.0, 2.0, 1.0)));
    return {triangle1, triangle2};
}

TEST(ObjectTest, Construct) {
    std::vector<Triangle> initialTriangles = makeObjectTriangles();
    Object object({initialTriangles[0], initialTriangles[1]});
    const auto &objectTriangles = object.getTriangles();

    EXPECT_EQ(objectTriangles.size(), 2);
    EXPECT_EQ(objectTriangles[0], initialTriangles[0]);
    EXPECT_EQ(objectTriangles[1], initialTriangles[1]);
}

TEST(ObjectTest, Translate) {
    std::vector<Triangle> initialTriangles = makeObjectTriangles();
    Object object({initialTriangles[0], initialTriangles[1]});

    Vector3 axe(1.0, 0.0, 0.0);
    double length = 10.0;
    object.translate(axe, length);

    const auto &objectTriangles = object.getTriangles();

    // glm matrices written by columns
    Matrix4 translationMatrix = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {10, 0, 0, 1},
    };

    EXPECT_EQ(objectTriangles[0], Triangle::linearTransform(translationMatrix, initialTriangles[0]));
    EXPECT_EQ(objectTriangles[1], Triangle::linearTransform(translationMatrix, initialTriangles[1]));
}

TEST(ObjectTest, Rotate) {
    std::vector<Triangle> initialTriangles = makeObjectTriangles();
    Object object({initialTriangles[0], initialTriangles[1]});

    Vector3 axe(0.0, 1.0, 0.0);
    double angle = std::numbers::pi / 2;
    object.rotate(axe, angle);
    const auto &objectTriangles = object.getTriangles();

    // glm matrices written by columns
    // | cos a  0   -sin a  0 |
    // | 0      1   0       0 |
    // | sin a  0   cos a   0 |
    // | 0      0   0       1 |
    Matrix4 rotationMatrix = {
        {0, 0, -1, 0},
        {0, 1, 0, 0},
        {1, 0, 0, 0},
        {0, 0, 0, 1},
    };

    EXPECT_EQ(objectTriangles[0], Triangle::linearTransform(rotationMatrix, initialTriangles[0]));
    EXPECT_EQ(objectTriangles[1], Triangle::linearTransform(rotationMatrix, initialTriangles[1]));

    ASSERT_DEATH(object.rotate(Vector3(0.0, 0.0, 0.0), angle), ".*");
}
