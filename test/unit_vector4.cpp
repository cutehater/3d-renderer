#include "vector4.h"
#include "gtest/gtest.h"

using namespace ScratchRenderer;

TEST(Vector4Test, Addition) {
    Vector4 v1(glm::dvec4(2.0, 4.0, 6.0, 2.0));
    Vector4 v2(4.0, 5.0, 6.0);
    Vector4 result = v1 + v2;

    EXPECT_DOUBLE_EQ(result.x, 5.0);
    EXPECT_DOUBLE_EQ(result.y, 7.0);
    EXPECT_DOUBLE_EQ(result.z, 9.0);
    EXPECT_DOUBLE_EQ(result.w, 1.0);
}

TEST(Vector4Test, Subtraction) {
    Vector4 v1(4.0, 5.0, 6.0);
    Vector4 v2(glm::dvec4(2.0, 4.0, 6.0, 2.0));
    Vector4 result = v1 - v2;

    EXPECT_DOUBLE_EQ(result.x, 3.0);
    EXPECT_DOUBLE_EQ(result.y, 3.0);
    EXPECT_DOUBLE_EQ(result.z, 3.0);
    EXPECT_DOUBLE_EQ(result.w, 1.0);
}

TEST(Vector4Test, ScalarMultiplication) {
    Vector4 v(glm::dvec4(2.0, 4.0, 6.0, 2.0));
    double k = 2.0;
    Vector4 result = v * k;

    EXPECT_DOUBLE_EQ(result.x, 2.0);
    EXPECT_DOUBLE_EQ(result.y, 4.0);
    EXPECT_DOUBLE_EQ(result.z, 6.0);
    EXPECT_DOUBLE_EQ(result.w, 1.0);
}

TEST(Vector4Test, ScalarDivision) {
    Vector4 v(2.0, 4.0, 6.0);
    double k = 2.0;
    Vector4 result = v / k;

    EXPECT_DOUBLE_EQ(result.x, 1.0);
    EXPECT_DOUBLE_EQ(result.y, 2.0);
    EXPECT_DOUBLE_EQ(result.z, 3.0);
    EXPECT_DOUBLE_EQ(result.w, 1.0);
}

TEST(Vector4Test, Equality) {
    Vector4 v1(1.0, 2.0, 3.0);
    Vector4 v2(2.0, 4.0, 6.0);
    Vector4 v3(glm::dvec4(2.0, 4.0, 6.0, 2.0));

    EXPECT_TRUE(v1 == v3);
    EXPECT_TRUE(v1 != v2);
}

TEST(Vector4Test, Normalize) {
    Vector4 v(glm::dvec4(2.0, 4.0, 6.0, 2.0));

    EXPECT_DOUBLE_EQ(v.x, 1.0);
    EXPECT_DOUBLE_EQ(v.y, 2.0);
    EXPECT_DOUBLE_EQ(v.z, 3.0);
    EXPECT_DOUBLE_EQ(v.w, 1.0);

    ASSERT_DEATH(Vector4(glm::dvec4(2.0, 4.0, 6.0, 0.0)), ".*");
}

TEST(Vector4Test, Length) {
    Vector4 v(glm::dvec4(2.0, 4.0, 6.0, 2.0));
    double length = v.length();

    EXPECT_DOUBLE_EQ(length, sqrt(14.0));
}
