#include "gtest/gtest.h"

#include <iostream>

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


class FarmLandTest : public ::testing::Test
{
public:
    FarmLandTest()
    : farmLand{{-5, 4}, {6, -8}},
      offSetFarmLand{{-5, 4}, {6, -8}}
    {
    }
    common::FarmLand farmLand;
    common::FarmLand offSetFarmLand;
};

TEST(FarmLand, AddBarrenPlot_SinglePlot_Succeeds)
{
    auto farmLand = common::FarmLand{{0, 0}, {4, 3}};
    ASSERT_EQ(farmLand.land.size(), 3);
    ASSERT_EQ(farmLand.land.front().size(), 4);

    for(const auto& row : farmLand.land)
    {
        for(const auto& plot : row)
        {
            ASSERT_EQ(plot, common::SoilStatus::Fertile);
        }
    }

    auto x = 2;
    auto y = 1;

    farmLand.AddBarrenPlot(common::Rectangle{{x, y}, {x + 1, y + 1}});

    EXPECT_EQ(farmLand.land[y][x], common::SoilStatus::Infertile);

    for(auto col = 0; col < farmLand.land.size(); ++col)
    {
        for(auto row = 0; row < farmLand.land.front().size(); ++row)
        {
            if(col != y && row != x)
            {
                EXPECT_EQ(farmLand.land[col][row], common::SoilStatus::Fertile);
            }
        }
    }
}

TEST(FarmLand, AddBarrenPlot_SinglePlotOffsetFarm_Succeeds)
{
    auto farmLand = common::FarmLand{{-5, 4}, {6, -8}};
    ASSERT_EQ(farmLand.land.size(), 12);
    ASSERT_EQ(farmLand.land.front().size(), 11);

    for(const auto& row : farmLand.land)
    {
        for(const auto& plot : row)
        {
            ASSERT_EQ(plot, common::SoilStatus::Fertile);
        }
    }

    auto x = -3;
    auto y = -7;

    farmLand.AddBarrenPlot(common::Rectangle{{x, y}, {x + 1, y + 1}});

    EXPECT_EQ(farmLand.land[y][x], common::SoilStatus::Infertile);

    for(auto col = 0; col < farmLand.land.size(); ++col)
    {
        for(auto row = 0; row < farmLand.land.front().size(); ++row)
        {
            if(col != y + farmLand.Bottom() && row != x + farmLand.Left())
            {
                EXPECT_EQ(farmLand.land[col][row], common::SoilStatus::Fertile);
            }
        }
    }
}

TEST(FarmLand, AddBarrenPlot_SinglePlotCorners_Succeeds)
{
    auto farmLand = common::FarmLand{{0, 0}, {4, 3}};
    ASSERT_EQ(farmLand.land.size(), 3);
    ASSERT_EQ(farmLand.land.front().size(), 4);

    EXPECT_EQ(farmLand.land[0][0], common::SoilStatus::Fertile);
    farmLand.AddBarrenPlot(common::Rectangle{{0, 0}, {1, 1}});
    EXPECT_EQ(farmLand.land[0][0], common::SoilStatus::Infertile);

    EXPECT_EQ(farmLand.land[0][3], common::SoilStatus::Fertile);
    farmLand.AddBarrenPlot(common::Rectangle{{3, 0}, {4, 1}});
    EXPECT_EQ(farmLand.land[0][3], common::SoilStatus::Infertile);

    EXPECT_EQ(farmLand.land[2][0], common::SoilStatus::Fertile);
    farmLand.AddBarrenPlot(common::Rectangle{{0, 2}, {1, 3}});
    EXPECT_EQ(farmLand.land[2][0], common::SoilStatus::Infertile);

    EXPECT_EQ(farmLand.land[2][3], common::SoilStatus::Fertile);
    farmLand.AddBarrenPlot(common::Rectangle{{3, 2}, {4, 3}});
    EXPECT_EQ(farmLand.land[2][3], common::SoilStatus::Infertile);
}

TEST(FarmLand, AddBarrenPlot_SinglePlotCornersOffsetFarm_Succeeds)
{
    auto offSetFarmLand = common::FarmLand{{-5, 4}, {6, -8}};
    ASSERT_EQ(offSetFarmLand.land.size(), 12);
    ASSERT_EQ(offSetFarmLand.land.front().size(), 11);

    EXPECT_EQ(offSetFarmLand.land[0][0], common::SoilStatus::Fertile);
    offSetFarmLand.AddBarrenPlot(common::Rectangle{{-5, -8}, {-4, -7}});
    EXPECT_EQ(offSetFarmLand.land[0][0], common::SoilStatus::Infertile);

    EXPECT_EQ(offSetFarmLand.land[0][10], common::SoilStatus::Fertile);
    offSetFarmLand.AddBarrenPlot(common::Rectangle{{5, -8}, {6, -7}});
    EXPECT_EQ(offSetFarmLand.land[0][10], common::SoilStatus::Infertile);

    EXPECT_EQ(offSetFarmLand.land[11][0], common::SoilStatus::Fertile);
    offSetFarmLand.AddBarrenPlot(common::Rectangle{{-5, 3}, {-4, 4}});
    EXPECT_EQ(offSetFarmLand.land[11][0], common::SoilStatus::Infertile);

    EXPECT_EQ(offSetFarmLand.land[11][10], common::SoilStatus::Fertile);
    offSetFarmLand.AddBarrenPlot(common::Rectangle{{5, 3}, {6, 4}});
    EXPECT_EQ(offSetFarmLand.land[11][10], common::SoilStatus::Infertile);
}