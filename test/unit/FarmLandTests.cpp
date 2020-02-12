#include "gtest/gtest.h"

#define private public
#include "FarmLand.cpp"
#undef private

TEST(FarmLand, Constructor_ValidDimensions_ReturnsFarmLand)
{
    auto expected = common::FarmLand{{0, 0}, {1, 2}};
    EXPECT_EQ(expected.land.size(), 2);
    EXPECT_EQ(expected.land.front().size(), 1);

    expected = common::FarmLand{{-3, -1}, {1, 2}};
    EXPECT_EQ(expected.land.size(), 3);
    EXPECT_EQ(expected.land.front().size(), 4);
}

TEST(FarmLand, Constructor_BadPoints_Throws)
{
    EXPECT_THROW({common::FarmLand({0, 0}, {0, 0});}, ParseException);
    EXPECT_THROW({common::FarmLand({1, 1}, {1, 1});}, ParseException);
    EXPECT_THROW({common::FarmLand({-1, -1}, {-1, -1});}, ParseException);
    EXPECT_THROW({common::FarmLand({0, 0}, {0, 1});}, ParseException);
    EXPECT_THROW({common::FarmLand({0, 0}, {1, 0});}, ParseException);
    EXPECT_THROW({common::FarmLand({1, 0}, {0, 0});}, ParseException);
    EXPECT_THROW({common::FarmLand({0, 1}, {0, 0});}, ParseException);
}