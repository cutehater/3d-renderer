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

TEST_F(ScreenTest, SetPixel) {
    size_t x = 10;
    size_t y = 20;
    screen_.setPixel(x, y, Color::Red);
    const auto &drawData = screen_.getDrawData();
    EXPECT_EQ(drawData[x * screen_.getHeight() + y].position, sf::Vector2f(10, 30));
    EXPECT_EQ(drawData[x * screen_.getHeight() + y].color, Color::Red);
}
