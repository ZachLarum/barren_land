#include "gtest/gtest.h"

#include <iostream>

#define private public
#include "FarmLand.cpp"
#undef private

TEST(FarmLand, Constructor_ValidDimensions_ReturnsFarmLand)
{
    auto actual = common::FarmLand{{0, 0}, {1, 2}};
    EXPECT_EQ(actual.land.size(), 2);
    EXPECT_EQ(actual.land.front().size(), 1);

    actual = common::FarmLand{{-3, -1}, {1, 2}};
    EXPECT_EQ(actual.land.size(), 3);
    EXPECT_EQ(actual.land.front().size(), 4);
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
    : xRight{6},
      xLeft{-5},
      yTop{4},
      yBottom{-8},
      origin{0},
      farmLand{{origin, origin}, {xRight, yTop}},
      offsetFarmLand{{xLeft, yTop}, {xRight, yBottom}}
    {
    }
    const int xRight;
    const int xLeft;
    const int yTop;
    const int yBottom;
    const int origin;
    common::FarmLand farmLand;
    common::FarmLand offsetFarmLand;
};

TEST_F(FarmLandTest, AddBarrenPlot_SinglePlot_Succeeds)
{
    ASSERT_EQ(farmLand.land.size(), yTop);
    ASSERT_EQ(farmLand.land.front().size(), xRight);

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

TEST_F(FarmLandTest, AddBarrenPlot_SinglePlotOffsetFarm_Succeeds)
{
    ASSERT_EQ(offsetFarmLand.land.size(), yTop - yBottom);
    ASSERT_EQ(offsetFarmLand.land.front().size(), xRight - xLeft);

    for(const auto& row : offsetFarmLand.land)
    {
        for(const auto& plot : row)
        {
            ASSERT_EQ(plot, common::SoilStatus::Fertile);
        }
    }

    auto x = -3;
    auto y = -5;

    offsetFarmLand.AddBarrenPlot(common::Rectangle{{x, y}, {x + 1, y + 1}});

    EXPECT_EQ(offsetFarmLand.land[y - offsetFarmLand.Bottom()][x - offsetFarmLand.Left()], common::SoilStatus::Infertile);

    for(auto col = 0; col < offsetFarmLand.land.size(); ++col)
    {
        for(auto row = 0; row < offsetFarmLand.land.front().size(); ++row)
        {
            if(col != y - offsetFarmLand.Bottom() && row != x - offsetFarmLand.Left())
            {
                EXPECT_EQ(offsetFarmLand.land[col][row], common::SoilStatus::Fertile);
            }
        }
    }
}

TEST_F(FarmLandTest, AddBarrenPlot_SinglePlotCorners_Succeeds)
{
    ASSERT_EQ(farmLand.land.size(), yTop);
    ASSERT_EQ(farmLand.land.front().size(), xRight);

    auto xMax = farmLand.Width() - 1;
    auto yMax = farmLand.Height() - 1;

    EXPECT_EQ(farmLand.land[0][0], common::SoilStatus::Fertile);
    farmLand.AddBarrenPlot(common::Rectangle{{origin, origin}, {origin + 1, origin + 1}});
    EXPECT_EQ(farmLand.land[0][0], common::SoilStatus::Infertile);

    EXPECT_EQ(farmLand.land[0][xMax], common::SoilStatus::Fertile);
    farmLand.AddBarrenPlot(common::Rectangle{{xRight - 1, origin}, {xRight, origin + 1}});
    EXPECT_EQ(farmLand.land[0][xMax], common::SoilStatus::Infertile);

    EXPECT_EQ(farmLand.land[yMax][0], common::SoilStatus::Fertile);
    farmLand.AddBarrenPlot(common::Rectangle{{origin, yTop - 1}, {origin + 1, yTop}});
    EXPECT_EQ(farmLand.land[yMax][0], common::SoilStatus::Infertile);

    EXPECT_EQ(farmLand.land[yMax][xMax], common::SoilStatus::Fertile);
    farmLand.AddBarrenPlot(common::Rectangle{{xRight - 1, yTop - 1}, {xRight, yTop}});
    EXPECT_EQ(farmLand.land[yMax][xMax], common::SoilStatus::Infertile);
}

TEST_F(FarmLandTest, AddBarrenPlot_SinglePlotCornersOffsetFarm_Succeeds)
{
    ASSERT_EQ(offsetFarmLand.land.size(), yTop - yBottom);
    ASSERT_EQ(offsetFarmLand.land.front().size(), xRight - xLeft);

    auto xMax = offsetFarmLand.Width() - 1;
    auto yMax = offsetFarmLand.Height() - 1;

    EXPECT_EQ(offsetFarmLand.land[0][0], common::SoilStatus::Fertile);
    offsetFarmLand.AddBarrenPlot(common::Rectangle{{xLeft, yBottom}, {xLeft + 1, yBottom + 1}});
    EXPECT_EQ(offsetFarmLand.land[0][0], common::SoilStatus::Infertile);

    EXPECT_EQ(offsetFarmLand.land[0][xMax], common::SoilStatus::Fertile);
    offsetFarmLand.AddBarrenPlot(common::Rectangle{{xRight - 1, yBottom}, {xRight, yBottom + 1}});
    EXPECT_EQ(offsetFarmLand.land[0][xMax], common::SoilStatus::Infertile);

    EXPECT_EQ(offsetFarmLand.land[yMax][0], common::SoilStatus::Fertile);
    offsetFarmLand.AddBarrenPlot(common::Rectangle{{xLeft, yTop - 1}, {xLeft + 1, yTop}});
    EXPECT_EQ(offsetFarmLand.land[yMax][0], common::SoilStatus::Infertile);

    EXPECT_EQ(offsetFarmLand.land[yMax][xMax], common::SoilStatus::Fertile);
    offsetFarmLand.AddBarrenPlot(common::Rectangle{{xRight - 1, yTop - 1}, {xRight, yTop}});
    EXPECT_EQ(offsetFarmLand.land[yMax][xMax], common::SoilStatus::Infertile);
}

TEST_F(FarmLandTest, FertilePlots_NoPlots_ReturnsArea)
{
    for(auto col = 0; col < farmLand.land.size(); ++col)
    {
        for(auto row = 0; row < farmLand.land.front().size(); ++row)
        {
            EXPECT_EQ(farmLand.land[col][row], common::SoilStatus::Fertile);
        }
    }

    auto plots = farmLand.FertilePlots();

    ASSERT_EQ(plots.size(), 1);

    EXPECT_EQ(plots[0], farmLand.Area());
}

TEST_F(FarmLandTest, FertilePlots_PlotsNotOnFarm_ReturnsArea)
{
    for(auto col = 0; col < farmLand.land.size(); ++col)
    {
        for(auto row = 0; row < farmLand.land.front().size(); ++row)
        {
            EXPECT_EQ(farmLand.land[col][row], common::SoilStatus::Fertile);
        }
    }

    farmLand.AddBarrenPlot(common::Rectangle{{origin, origin}, {-xRight, -yTop}});
    farmLand.AddBarrenPlot(common::Rectangle{{xRight + 5, yTop + 5}, {xRight, yTop}});
    farmLand.AddBarrenPlot(common::Rectangle{{origin, yTop}, {origin - 1, yTop + 5}});
    farmLand.AddBarrenPlot(common::Rectangle{{xRight, origin}, {xRight + 5, origin - 1}});
    farmLand.AddBarrenPlot(common::Rectangle{{origin , yTop/2}, {origin - 1, yTop/2 + 1}});
    farmLand.AddBarrenPlot(common::Rectangle{{xRight/2 , origin}, {xRight/2 + 1, origin - 1}});
    farmLand.AddBarrenPlot(common::Rectangle{{xRight , yTop/2}, {xRight + 1, yTop/2 + 1}});
    farmLand.AddBarrenPlot(common::Rectangle{{xRight/2 , yTop}, {xRight/2 + 1, yTop + 1}});

    auto plots = farmLand.FertilePlots();

    ASSERT_EQ(plots.size(), 1);

    EXPECT_EQ(plots[0], farmLand.Area());
}

TEST_F(FarmLandTest, FertilePlots_FarmSizePlot_ReturnsNothing)
{
    for(auto col = 0; col < farmLand.land.size(); ++col)
    {
        for(auto row = 0; row < farmLand.land.front().size(); ++row)
        {
            EXPECT_EQ(farmLand.land[col][row], common::SoilStatus::Fertile);
        }
    }

    farmLand.AddBarrenPlot(common::Rectangle{{origin, origin}, {xRight, yTop}});

    auto plots = farmLand.FertilePlots();

    ASSERT_EQ(plots.size(), 0);
}

TEST_F(FarmLandTest, FertilePlots_PlotOverExtendingFarm_ReturnsNothing)
{
    for(auto col = 0; col < farmLand.land.size(); ++col)
    {
        for(auto row = 0; row < farmLand.land.front().size(); ++row)
        {
            EXPECT_EQ(farmLand.land[col][row], common::SoilStatus::Fertile);
        }
    }

    farmLand.AddBarrenPlot(common::Rectangle{{origin - 5, origin - 5}, {xRight + 5, yTop + 5}});

    auto plots = farmLand.FertilePlots();

    ASSERT_EQ(plots.size(), 0);
}

TEST_F(FarmLandTest, FertilePlots_SinglePlot_ReturnsOnePlotOneLessThanArea)
{
    for(auto col = 0; col < farmLand.land.size(); ++col)
    {
        for(auto row = 0; row < farmLand.land.front().size(); ++row)
        {
            EXPECT_EQ(farmLand.land[col][row], common::SoilStatus::Fertile);
        }
    }

    farmLand.AddBarrenPlot(common::Rectangle{{origin, origin}, {origin + 1, origin + 1}});

    auto plots = farmLand.FertilePlots();
    ASSERT_EQ(plots.size(), 1);
    EXPECT_EQ(plots[0], farmLand.Area() - 1);
}

TEST_F(FarmLandTest, FertilePlots_SinglePlotCutsFarmInTwo_ReturnsTwo)
{
    for(auto col = 0; col < farmLand.land.size(); ++col)
    {
        for(auto row = 0; row < farmLand.land.front().size(); ++row)
        {
            EXPECT_EQ(farmLand.land[col][row], common::SoilStatus::Fertile);
        }
    }

    farmLand.AddBarrenPlot(common::Rectangle{{origin, yTop/2}, {xRight, yTop/2 + 1}});

    auto plots = farmLand.FertilePlots();

    ASSERT_EQ(plots.size(), 2);

    auto isYEven = yTop % 2 == 0;
    auto firstHalf = isYEven ? farmLand.Height() / 2 - 1 : farmLand.Height() / 2;
    EXPECT_EQ(plots[0], farmLand.Width() * firstHalf);
    EXPECT_EQ(plots[1], farmLand.Width() * farmLand.Height() / 2);
}

TEST_F(FarmLandTest, FertilePlots_TwoPlotsCutsFarmInFour_ReturnsFour)
{
    for(auto col = 0; col < farmLand.land.size(); ++col)
    {
        for(auto row = 0; row < farmLand.land.front().size(); ++row)
        {
            EXPECT_EQ(farmLand.land[col][row], common::SoilStatus::Fertile);
        }
    }

    farmLand.AddBarrenPlot(common::Rectangle{{origin, yTop/2}, {xRight, yTop/2 + 1}});
    farmLand.AddBarrenPlot(common::Rectangle{{xRight/2, origin}, {xRight/2 + 1, yTop}});

    auto plots = farmLand.FertilePlots();

    ASSERT_EQ(plots.size(), 4);

    auto isYEven = yTop % 2 == 0;
    auto yFirstHalf = isYEven ? farmLand.Height() / 2 - 1 : farmLand.Height() / 2;
    auto isXEven = xRight % 2 == 0;
    auto xFirstHalf = isXEven ? farmLand.Width() / 2 - 1 : farmLand.Width() / 2;

    EXPECT_EQ(plots[0], xFirstHalf * yFirstHalf);
    EXPECT_EQ(plots[1], farmLand.Width() / 2 * yFirstHalf);
    EXPECT_EQ(plots[2], xFirstHalf * farmLand.Height() / 2);
    EXPECT_EQ(plots[3], farmLand.Width() / 2 * farmLand.Height() / 2);
}

