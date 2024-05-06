#include "camera.h"
#include "configuration.h"
#include "gtest/gtest.h"

#include <array>
#include <numbers>
#include <utility>
#include <vector>

using namespace ScratchRenderer;
using Vertex = Primitives::Vertex;
using Triangle = Primitives::Triangle;

TEST(CameraTest, ProjectVisibleTriangle) {
    Camera camera;
    Triangle visibleTriangle(Vertex(Vector4(3.0, 4.0, configuration::kNearPlaneDist + Epsilon)),
                             Vertex(Vector4(1.0, 5.0, configuration::kNearPlaneDist + Epsilon)),
                             Vertex(Vector4(11.0, 20.5, configuration::kNearPlaneDist + Epsilon)));
    World world;
    world.addObject(Object({visibleTriangle}));
    std::vector<Triangle> cameraProjection = camera.projectWorldObjects(world);

    EXPECT_EQ(cameraProjection.size(), 1);
    EXPECT_EQ(cameraProjection[0], Triangle::linearTransform(camera.getProjectionMatrix(), visibleTriangle));
}

TEST(CameraTest, ProjectInvisibleTriangle) {
    Camera camera;
    Triangle invisibleTriangle(Vertex(Vector4(0.0, 0.0, configuration::kNearPlaneDist - Epsilon)),
                               Vertex(Vector4(1.0, 0.0, configuration::kNearPlaneDist - Epsilon)),
                               Vertex(Vector4(0.0, 1.0, configuration::kNearPlaneDist - Epsilon)));
    World world;
    world.addObject(Object({invisibleTriangle}));
    std::vector<Triangle> cameraProjection = camera.projectWorldObjects(world);

    EXPECT_EQ(cameraProjection.size(), 0);
}

TEST(CameraTest, ProjectOneVisibleVertexClippedTriangle) {
    Triangle oneVisibleVertexTriangle(Vertex(Vector4(0.0, 0.0, configuration::kNearPlaneDist + 2)),
                                      Vertex(Vector4(1.0, 0.0, configuration::kNearPlaneDist - 1)),
                                      Vertex(Vector4(-1.0, 0.0, configuration::kNearPlaneDist - 1)));
    Triangle oneVisibleVertexClippedTriangle(Vertex(Vector4(0.0, 0.0, configuration::kNearPlaneDist + 2)),
                                             Vertex(Vector4(2.0 / 3.0, 0.0, configuration::kNearPlaneDist)),
                                             Vertex(Vector4(-2.0 / 3.0, 0.0, configuration::kNearPlaneDist)));

    Camera camera;
    World world;
    world.addObject(Object({oneVisibleVertexTriangle}));
    std::vector<Triangle> cameraProjection = camera.projectWorldObjects(world);

    EXPECT_EQ(cameraProjection.size(), 1);
    EXPECT_EQ(cameraProjection[0],
              Triangle::linearTransform(camera.getProjectionMatrix(), oneVisibleVertexClippedTriangle));
}

TEST(CameraTest, ProjectTwoVisibleVerticesClippedTriangle) {
    Triangle twoVisibleVerticesTriangle(Vertex(Vector4(1.0, 0.0, configuration::kNearPlaneDist + 2)),
                                        Vertex(Vector4(-1.0, 0.0, configuration::kNearPlaneDist + 2)),
                                        Vertex(Vector4(0.0, 0.0, configuration::kNearPlaneDist - 1)));
    std::vector<Vertex> clippedVertices{
        Vertex(Vector4(1.0, 0.0, configuration::kNearPlaneDist + 2)),
        Vertex(Vector4(-1.0, 0.0, configuration::kNearPlaneDist + 2)),
        Vertex(Vector4(-1.0 / 3.0, 0.0, configuration::kNearPlaneDist)),
        Vertex(Vector4(1.0 / 3.0, 0.0, configuration::kNearPlaneDist)),
    };
    std::vector<Triangle> clippedTrianglesVariant1{
        Triangle(clippedVertices[0], clippedVertices[1], clippedVertices[2]),
        Triangle(clippedVertices[0], clippedVertices[2], clippedVertices[3])};
    std::vector<Triangle> clippedTrianglesVariant2{
        Triangle(clippedVertices[0], clippedVertices[1], clippedVertices[3]),
        Triangle(clippedVertices[1], clippedVertices[2], clippedVertices[3])};

    Camera camera;
    World world;
    world.addObject(Object({twoVisibleVerticesTriangle}));
    std::vector<Triangle> cameraProjection = camera.projectWorldObjects(world);

    clippedTrianglesVariant1[0] =
        Triangle::linearTransform(camera.getProjectionMatrix(), clippedTrianglesVariant1[0]);
    clippedTrianglesVariant1[1] =
        Triangle::linearTransform(camera.getProjectionMatrix(), clippedTrianglesVariant1[1]);
    clippedTrianglesVariant2[0] =
        Triangle::linearTransform(camera.getProjectionMatrix(), clippedTrianglesVariant2[0]);
    clippedTrianglesVariant2[1] =
        Triangle::linearTransform(camera.getProjectionMatrix(), clippedTrianglesVariant2[1]);

    EXPECT_EQ(cameraProjection.size(), 2);
    EXPECT_TRUE((clippedTrianglesVariant1[0] == cameraProjection[0] &&
                 clippedTrianglesVariant1[1] == cameraProjection[1]) ||
                (clippedTrianglesVariant1[1] == cameraProjection[0] &&
                 clippedTrianglesVariant1[0] == cameraProjection[1]) ||
                (clippedTrianglesVariant2[0] == cameraProjection[0] &&
                 clippedTrianglesVariant2[1] == cameraProjection[1]) ||
                (clippedTrianglesVariant2[1] == cameraProjection[0] &&
                 clippedTrianglesVariant2[0] == cameraProjection[1]));
}

TEST(CameraTest, Translate) {
    Camera camera;
    Vector3 axe = Vector3(1, 2, 1);
    double coef = 0.5;
    camera.translate(axe, coef);

    std::array<Vertex, 3> vertices{Vertex(Vector4(3.0, 4.0, configuration::kNearPlaneDist + 2)),
                                   Vertex(Vector4(1.0, 5.0, configuration::kNearPlaneDist + 2)),
                                   Vertex(Vector4(11.0, 20.5, configuration::kNearPlaneDist + 2))};
    Triangle visibleTriangle(vertices);
    std::array<Vertex, 3> translatedVertices;
    for (size_t i = 0; i < 3; ++i) {
        translatedVertices[i] = Vertex(vertices[i].getPosition() - Vector4(axe * coef));
    }
    Triangle translatedVisibleTriangle(translatedVertices);

    World world;
    world.addObject(Object({visibleTriangle}));
    std::vector<Triangle> cameraProjection = camera.projectWorldObjects(world);

    EXPECT_EQ(cameraProjection.size(), 1);
    EXPECT_EQ(cameraProjection[0],
              Triangle::linearTransform(camera.getProjectionMatrix(), translatedVisibleTriangle));
}

TEST(CameraTest, Rotate) {
    Camera camera;
    Vector3 axe = Vector3(0, 0, 1);
    double angle = std::numbers::pi / 2;
    camera.rotate(axe, angle);

    // glm matrices written by columns
    // | cos a  -sin a  0  0 |
    // | sin a  cos a   0  0 |
    // | 0      0       1  0 |
    // | 0      0       0  1 |
    Matrix4 rotationMatrix = {
        {0, -1, 0, 0},
        {1, 0, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
    };

    Triangle visibleTriangle(Vertex(Vector4(3.0, 4.0, configuration::kNearPlaneDist + 2)),
                             Vertex(Vector4(1.0, 5.0, configuration::kNearPlaneDist + 2)),
                             Vertex(Vector4(11.0, 20.5, configuration::kNearPlaneDist + 2)));
    Triangle rotatedVisibleTriangle =
        Triangle::linearTransform(glm::transpose(rotationMatrix), visibleTriangle);

    World world;
    world.addObject(Object({visibleTriangle}));
    std::vector<Triangle> cameraProjection = camera.projectWorldObjects(world);

    EXPECT_EQ(cameraProjection.size(), 1);
    EXPECT_EQ(cameraProjection[0],
              Triangle::linearTransform(camera.getProjectionMatrix(), rotatedVisibleTriangle));

    ASSERT_DEATH(camera.rotate(Vector3(0, 0, 0), angle), ".*");
}

TEST(CameraTest, RotateThanTranslate) {
    Camera camera;
    Vector3 rotationAxe = Vector3(0, 0, 1);
    double angle = std::numbers::pi / 2;
    camera.rotate(rotationAxe, angle);
    Vector3 translationAxe = Vector3(1, 2, 1);
    double coef = 0.5;
    camera.translate(translationAxe, coef);

    // glm matrices written by columns
    // | cos a  -sin a  0  0 |
    // | sin a  cos a   0  0 |
    // | 0      0       1  0 |
    // | 0      0       0  1 |
    Matrix4 rotationMatrix = {
        {0, -1, 0, 0},
        {1, 0, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
    };

    std::array<Vertex, 3> vertices{Vertex(Vector4(3.0, 4.0, configuration::kNearPlaneDist + 2)),
                                   Vertex(Vector4(1.0, 5.0, configuration::kNearPlaneDist + 2)),
                                   Vertex(Vector4(11.0, 20.5, configuration::kNearPlaneDist + 2))};
    Triangle visibleTriangle(vertices);
    std::array<Vertex, 3> translatedVertices;
    for (size_t i = 0; i < 3; ++i) {
        translatedVertices[i] =
            Vertex(vertices[i].getPosition() - Vector4(rotationMatrix * Vector4(translationAxe * coef)));
    }
    Triangle resultTriangle =
        Triangle::linearTransform(glm::transpose(rotationMatrix), Triangle(translatedVertices));

    World world;
    world.addObject(Object({visibleTriangle}));
    std::vector<Triangle> cameraProjection = camera.projectWorldObjects(world);

    EXPECT_EQ(cameraProjection.size(), 1);
    EXPECT_EQ(cameraProjection[0], Triangle::linearTransform(camera.getProjectionMatrix(), resultTriangle));
}
