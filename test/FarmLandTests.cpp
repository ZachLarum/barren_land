#include "gtest/gtest.h"

#include <iostream>

#define private public
#include "FarmLand.cpp"
#undef private

TEST(FarmLand, Constructor_ValidDimensions_ReturnsFarmLand)
{
    auto actual = common::FarmLand{{0, 0}, {1, 2}};
    EXPECT_EQ(actual.plots.size(), 2);
    EXPECT_EQ(actual.plots.front().size(), 1);

    actual = common::FarmLand{{-3, -1}, {1, 2}};
    EXPECT_EQ(actual.plots.size(), 3);
    EXPECT_EQ(actual.plots.front().size(), 4);
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

    virtual void SetUp() override
    {
        ASSERT_EQ(offsetFarmLand.plots.size(), yTop - yBottom);
        ASSERT_EQ(offsetFarmLand.plots.front().size(), xRight - xLeft);
        EXPECT_TRUE(IsEveryPlotFertile());
    }

    bool IsEveryPlotFertile()
    {
        for(auto col = 0; col < farmLand.plots.size(); ++col)
        {
            for(auto row = 0; row < farmLand.plots.front().size(); ++row)
            {
                if(farmLand.plots[col][row] != common::SoilStatus::Fertile)
                {
                    return false;
                }
            }
        }
        return true;
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
    auto x = 2;
    auto y = 1;

    farmLand.AddBarrenPlot(common::Land{{x, y}, {x + 1, y + 1}});

    EXPECT_EQ(farmLand.plots[y][x], common::SoilStatus::Infertile);

    for(auto col = 0; col < farmLand.plots.size(); ++col)
    {
        for(auto row = 0; row < farmLand.plots.front().size(); ++row)
        {
            if(col != y && row != x)
            {
                EXPECT_EQ(farmLand.plots[col][row], common::SoilStatus::Fertile);
            }
        }
    }
}

TEST_F(FarmLandTest, AddBarrenPlot_SinglePlotOffsetFarm_Succeeds)
{
    auto x = -3;
    auto y = -5;

    offsetFarmLand.AddBarrenPlot(common::Land{{x, y}, {x + 1, y + 1}});

    EXPECT_EQ(offsetFarmLand.plots[y - offsetFarmLand.Bottom()][x - offsetFarmLand.Left()], common::SoilStatus::Infertile);

    for(auto col = 0; col < offsetFarmLand.plots.size(); ++col)
    {
        for(auto row = 0; row < offsetFarmLand.plots.front().size(); ++row)
        {
            if(col != y - offsetFarmLand.Bottom() && row != x - offsetFarmLand.Left())
            {
                EXPECT_EQ(offsetFarmLand.plots[col][row], common::SoilStatus::Fertile);
            }
        }
    }
}

TEST_F(FarmLandTest, AddBarrenPlot_SinglePlotCorners_Succeeds)
{
    auto xMax = farmLand.Width() - 1;
    auto yMax = farmLand.Height() - 1;

    EXPECT_EQ(farmLand.plots[0][0], common::SoilStatus::Fertile);
    farmLand.AddBarrenPlot(common::Land{{origin, origin}, {origin + 1, origin + 1}});
    EXPECT_EQ(farmLand.plots[0][0], common::SoilStatus::Infertile);

    EXPECT_EQ(farmLand.plots[0][xMax], common::SoilStatus::Fertile);
    farmLand.AddBarrenPlot(common::Land{{xRight - 1, origin}, {xRight, origin + 1}});
    EXPECT_EQ(farmLand.plots[0][xMax], common::SoilStatus::Infertile);

    EXPECT_EQ(farmLand.plots[yMax][0], common::SoilStatus::Fertile);
    farmLand.AddBarrenPlot(common::Land{{origin, yTop - 1}, {origin + 1, yTop}});
    EXPECT_EQ(farmLand.plots[yMax][0], common::SoilStatus::Infertile);

    EXPECT_EQ(farmLand.plots[yMax][xMax], common::SoilStatus::Fertile);
    farmLand.AddBarrenPlot(common::Land{{xRight - 1, yTop - 1}, {xRight, yTop}});
    EXPECT_EQ(farmLand.plots[yMax][xMax], common::SoilStatus::Infertile);
}

TEST_F(FarmLandTest, AddBarrenPlot_SinglePlotCornersOffsetFarm_Succeeds)
{
    auto xMax = offsetFarmLand.Width() - 1;
    auto yMax = offsetFarmLand.Height() - 1;

    EXPECT_EQ(offsetFarmLand.plots[0][0], common::SoilStatus::Fertile);
    offsetFarmLand.AddBarrenPlot(common::Land{{xLeft, yBottom}, {xLeft + 1, yBottom + 1}});
    EXPECT_EQ(offsetFarmLand.plots[0][0], common::SoilStatus::Infertile);

    EXPECT_EQ(offsetFarmLand.plots[0][xMax], common::SoilStatus::Fertile);
    offsetFarmLand.AddBarrenPlot(common::Land{{xRight - 1, yBottom}, {xRight, yBottom + 1}});
    EXPECT_EQ(offsetFarmLand.plots[0][xMax], common::SoilStatus::Infertile);

    EXPECT_EQ(offsetFarmLand.plots[yMax][0], common::SoilStatus::Fertile);
    offsetFarmLand.AddBarrenPlot(common::Land{{xLeft, yTop - 1}, {xLeft + 1, yTop}});
    EXPECT_EQ(offsetFarmLand.plots[yMax][0], common::SoilStatus::Infertile);

    EXPECT_EQ(offsetFarmLand.plots[yMax][xMax], common::SoilStatus::Fertile);
    offsetFarmLand.AddBarrenPlot(common::Land{{xRight - 1, yTop - 1}, {xRight, yTop}});
    EXPECT_EQ(offsetFarmLand.plots[yMax][xMax], common::SoilStatus::Infertile);
}

TEST_F(FarmLandTest, FertilePlots_NoPlots_ReturnsArea)
{
    auto plots = farmLand.FertilePlots();

    ASSERT_EQ(plots.size(), 1);

    EXPECT_EQ(plots[0], farmLand.Area());
}

TEST_F(FarmLandTest, FertilePlots_PlotsNotOnFarm_ReturnsArea)
{
    farmLand.AddBarrenPlot(common::Land{{origin, origin}, {-xRight, -yTop}});
    farmLand.AddBarrenPlot(common::Land{{xRight + 5, yTop + 5}, {xRight, yTop}});
    farmLand.AddBarrenPlot(common::Land{{origin, yTop}, {origin - 1, yTop + 5}});
    farmLand.AddBarrenPlot(common::Land{{xRight, origin}, {xRight + 5, origin - 1}});
    farmLand.AddBarrenPlot(common::Land{{origin , yTop / 2}, {origin - 1, yTop / 2 + 1}});
    farmLand.AddBarrenPlot(common::Land{{xRight / 2 , origin}, {xRight / 2 + 1, origin - 1}});
    farmLand.AddBarrenPlot(common::Land{{xRight , yTop / 2}, {xRight + 1, yTop / 2 + 1}});
    farmLand.AddBarrenPlot(common::Land{{xRight / 2 , yTop}, {xRight / 2 + 1, yTop + 1}});

    auto plots = farmLand.FertilePlots();

    ASSERT_EQ(plots.size(), 1);

    EXPECT_EQ(plots[0], farmLand.Area());
}

TEST_F(FarmLandTest, FertilePlots_FarmSizePlot_ReturnsNothing)
{
    farmLand.AddBarrenPlot(common::Land{{origin, origin}, {xRight, yTop}});

    auto plots = farmLand.FertilePlots();

    ASSERT_EQ(plots.size(), 0);
}

TEST_F(FarmLandTest, FertilePlots_PlotOverExtendingFarm_ReturnsNothing)
{
    farmLand.AddBarrenPlot(common::Land{{origin - 5, origin - 5}, {xRight + 5, yTop + 5}});

    auto plots = farmLand.FertilePlots();

    ASSERT_EQ(plots.size(), 0);
}

TEST_F(FarmLandTest, FertilePlots_SinglePlot_ReturnsOnePlotOneLessThanArea)
{
    farmLand.AddBarrenPlot(common::Land{{origin, origin}, {origin + 1, origin + 1}});

    auto plots = farmLand.FertilePlots();
    ASSERT_EQ(plots.size(), 1);
    EXPECT_EQ(plots[0], farmLand.Area() - 1);
}

TEST_F(FarmLandTest, FertilePlots_SinglePlotCutsFarmInTwo_ReturnsTwo)
{
    farmLand.AddBarrenPlot(common::Land{{origin, yTop / 2}, {xRight, yTop / 2 + 1}});

    auto plots = farmLand.FertilePlots();

    ASSERT_EQ(plots.size(), 2);

    auto isYEven = yTop % 2 == 0;
    auto firstHalf = isYEven ? farmLand.Height() / 2 - 1 : farmLand.Height() / 2;
    EXPECT_EQ(plots[0], farmLand.Width() * firstHalf);
    EXPECT_EQ(plots[1], farmLand.Width() * farmLand.Height() / 2);
}

TEST_F(FarmLandTest, FertilePlots_TwoPlotsCutsFarmInFour_ReturnsFour)
{
    farmLand.AddBarrenPlot(common::Land{{origin, yTop / 2}, {xRight, yTop / 2 + 1}});
    farmLand.AddBarrenPlot(common::Land{{xRight / 2, origin}, {xRight / 2 + 1, yTop}});

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

TEST_F(FarmLandTest, IsPointInBounds_PointsInBounds_ReturnTrue)
{
    EXPECT_TRUE(farmLand.IsPointInBounds({origin, origin}));
    EXPECT_TRUE(farmLand.IsPointInBounds({xRight - 1, origin}));
    EXPECT_TRUE(farmLand.IsPointInBounds({origin, yTop - 1}));
    EXPECT_TRUE(farmLand.IsPointInBounds({xRight - 1, yTop - 1}));
    EXPECT_TRUE(farmLand.IsPointInBounds({xRight / 2, yTop / 2}));
}

TEST_F(FarmLandTest, IsPointInBounds_PointsOutOfBounds_ReturnFalse)
{
    EXPECT_FALSE(farmLand.IsPointInBounds({origin -1, origin - 1}));
    EXPECT_FALSE(farmLand.IsPointInBounds({origin, origin - 1}));
    EXPECT_FALSE(farmLand.IsPointInBounds({origin - 1, origin}));

    EXPECT_FALSE(farmLand.IsPointInBounds({xRight, origin}));
    EXPECT_FALSE(farmLand.IsPointInBounds({xRight, origin - 1}));
    EXPECT_FALSE(farmLand.IsPointInBounds({xRight - 1, origin - 1}));

    EXPECT_FALSE(farmLand.IsPointInBounds({origin, yTop}));
    EXPECT_FALSE(farmLand.IsPointInBounds({origin - 1, yTop}));
    EXPECT_FALSE(farmLand.IsPointInBounds({origin - 1, yTop - 1}));

    EXPECT_FALSE(farmLand.IsPointInBounds({xRight, yTop}));
    EXPECT_FALSE(farmLand.IsPointInBounds({xRight - 1, yTop}));
    EXPECT_FALSE(farmLand.IsPointInBounds({xRight, yTop - 1}));
}

TEST_F(FarmLandTest, GetSoilStatus_PointInBounds_ReturnsCorrectStatus)
{
    farmLand.AddBarrenPlot({{0,0}, {1,1}});

    EXPECT_EQ(farmLand.GetSoilStatus({0,0}), common::SoilStatus::Infertile);
    EXPECT_EQ(farmLand.GetSoilStatus({0,1}), common::SoilStatus::Fertile);
}

TEST_F(FarmLandTest, GetSoilStatus_PointOutOfBounds_ReturnOutOfBounds)
{
    EXPECT_EQ(farmLand.GetSoilStatus({-1,-1}), common::SoilStatus::OutOfBounds);
}

TEST_F(FarmLandTest, SetSoilStatus_PointInBounds_SetsSoilStatus)
{
    farmLand.SetSoilStatus({0,0}, common::SoilStatus::Infertile);
    EXPECT_EQ(farmLand.GetSoilStatus({0,0}), common::SoilStatus::Infertile);
}

TEST_F(FarmLandTest, SetSoilStatus_PointOutOfBounds_DoesNotThrow)
{
    EXPECT_NO_THROW(farmLand.SetSoilStatus({-1,-1}, common::SoilStatus::Infertile));
}

TEST_F(FarmLandTest, FindSurroundingFertilePoints_AllAdjacentPointsFertile_ReturnsFourPoints)
{
    auto points = farmLand.FindSurroudingFertilePoints({1,1});

    ASSERT_EQ(points.size(), 4);

    auto expected = std::vector<common::Point>{{0, 1}, {1, 0}, {2, 1}, {1, 2}};
    for(const auto& p : expected)
    {
        EXPECT_TRUE(
            std::any_of(points.begin(), points.end(),
                [&p](const auto& e)
                {
                    return e.x == p.x && e.y == p.y;
                }));
    }
}

TEST_F(FarmLandTest, FindSurroundingFertilePoints_CornerPlotAllAdjacentAreFertile_ReturnsTwoPoints)
{
    auto points = farmLand.FindSurroudingFertilePoints({0,0});

    ASSERT_EQ(points.size(), 2);

    auto expected = std::vector<common::Point>{{0, 1}, {1, 0}};
    for(const auto& p : expected)
    {
        EXPECT_TRUE(
            std::any_of(points.begin(), points.end(),
                [&p](const auto& e)
                {
                    return e.x == p.x && e.y == p.y;
                }));
    }
}

TEST_F(FarmLandTest, FindSurroundingFertilePoints_HalfAdjacentAreFertile_ReturnsTwoPoints)
{
    farmLand.SetSoilStatus({1, 2}, common::SoilStatus::Infertile);
    farmLand.SetSoilStatus({2, 1}, common::SoilStatus::Infertile);
    auto points = farmLand.FindSurroudingFertilePoints({1,1});

    ASSERT_EQ(points.size(), 2);

    auto expected = std::vector<common::Point>{{0, 1}, {1, 0}};
    for(const auto& p : expected)
    {
        EXPECT_TRUE(
            std::any_of(points.begin(), points.end(),
                [&p](const auto& e)
                {
                    return e.x == p.x && e.y == p.y;
                }));
    }
}

TEST_F(FarmLandTest, FindSizeOfPlot_AllFertile_ReturnsArea)
{
    auto area = farmLand.FindSizeOfPlot({1,1});

    ASSERT_EQ(area, xRight * yTop);
}

TEST_F(FarmLandTest, FindSizeOfPlot_FourPlotsInfertile_ReturnsAreaMinusFour)
{
    farmLand.SetSoilStatus({0,0}, common::SoilStatus::Infertile);
    farmLand.SetSoilStatus({3, yTop - 2}, common::SoilStatus::Infertile);
    farmLand.SetSoilStatus({xRight - 1, 1}, common::SoilStatus::Infertile);
    farmLand.SetSoilStatus({3,3}, common::SoilStatus::Infertile);
    auto area = farmLand.FindSizeOfPlot({1,1});

    ASSERT_EQ(area, xRight * yTop - 4);
}

TEST_F(FarmLandTest, FindSizeOfPlot_Infertile_ReturnsZero)
{
    farmLand.SetSoilStatus({1,1}, common::SoilStatus::Infertile);
    auto area = farmLand.FindSizeOfPlot({1,1});

    ASSERT_EQ(area, 0);
}



