#include "world.h"
#include "gtest/gtest.h"

#include <vector>

using namespace ScratchRenderer;
using Triangle = Primitives::Triangle;
using Vertex = Primitives::Vertex;

std::vector<Triangle> makeObjectsTriangles() {
    Triangle triangle1(Vertex(Vector4(1.0, 0.0, 0.0)), Vertex(Vector4(0.0, 1.0, 0.0)),
                       Vertex(Vector4(0.0, 0.0, 1.0)));
    Triangle triangle2(Vertex(Vector4(-1.0, 0.0, -1.0)), Vertex(Vector4(0.0, -1.0, 2.0)),
                       Vertex(Vector4(3.0, 2.0, 1.0)));
    Triangle triangle3(Vertex(Vector4(0.0, 0.0, 0.0)), Vertex(Vector4(0.0, 5.0, 10.0)),
                       Vertex(Vector4(11.0, -4.0, 7.0)));

    return {triangle1, triangle2, triangle3};
}

TEST(WorldTest, ConstructAndIterate) {
    World world;
    std::vector<Triangle> triangles = makeObjectsTriangles();
    world.addObject(Object({triangles[0], triangles[1]}));
    world.addObject(Object({triangles[2]}));

    EXPECT_EQ(world.size(), 3);

    size_t triangleIdx = 0;
    for (const Triangle &triangle : world) {
        EXPECT_EQ(triangle, triangles[triangleIdx]);
        ++triangleIdx;
    }
}
