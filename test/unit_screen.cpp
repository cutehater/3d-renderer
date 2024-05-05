#include "screen.h"
#include "gtest/gtest.h"

using namespace ScratchRenderer;

class ScreenTest : public ::testing::Test {
protected:
    ScreenTest() : screen_(100, 50) {}

    Screen screen_;
};

TEST_F(ScreenTest, Constructor) {
    EXPECT_EQ(screen_.getWidth(), 100);
    EXPECT_EQ(screen_.getHeight(), 50);
}

TEST_F(ScreenTest, ProjectVertexToScreenAndDiscretize) {
    Primitives::Vertex v(Vector4(0.5, -0.5, 77), Color::White);
    auto projected = screen_.projectVertexToScreenAndDiscretize(v);
    EXPECT_EQ(projected.x, 75);
    EXPECT_EQ(projected.y, 12);
}

TEST_F(ScreenTest, SetPixel) {
    screen_.setPixel(10, 20, Color::Red);
    const auto &drawData = screen_.getDrawData();
    EXPECT_EQ(drawData.size(), 1);
    EXPECT_EQ(drawData[0].position, sf::Vector2f(10, 30));
    EXPECT_EQ(drawData[0].color, Color::Red);

    screen_.setPixel(101, 20, Color::Green);
    screen_.setPixel(10, 51, Color::Blue);
    EXPECT_EQ(drawData.size(), 1);
}

TEST_F(ScreenTest, Clear) {
    screen_.setPixel(10, 20, Color::Red);
    screen_.setPixel(20, 30, Color::Green);
    screen_.clear();
    const auto &drawData = screen_.getDrawData();
    EXPECT_EQ(drawData.size(), 0);
}
