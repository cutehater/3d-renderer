#include "storage2d.h"
#include "gtest/gtest.h"

using namespace ScratchRenderer;

TEST(Storage2DTest, SetAndGetElements) {
    Storage2D<int> storage(2, 3);
    storage(0, 0) = 1;
    storage(0, 1) = 2;
    storage(1, 0) = 3;
    storage(1, 1) = 4;

    EXPECT_EQ(storage(0, 0), 1);
    EXPECT_EQ(storage(0, 1), 2);
    EXPECT_EQ(storage(1, 0), 3);
    EXPECT_EQ(storage(1, 1), 4);
}

TEST(Storage2DTest, OutOfBounds) {
    Storage2D<int> storage(2, 3);

    ASSERT_DEATH({ storage(2, 0); }, "index out of storage bound");
    ASSERT_DEATH({ storage(0, 3); }, "index out of storage bound");
}

TEST(Storage2DTest, Clear) {
    Storage2D<int> storage(2, 3);

    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            storage(i, j) = 228;
        }
    }

    storage.clear();

    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            EXPECT_EQ(storage(i, j), 0);
        }
    }
}
