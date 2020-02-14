#include "FarmLand.hpp"

#include "Exception.hpp"

#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>

namespace common
{
FarmLand::FarmLand(Point corner1, Point corner2)
  : common::Land{corner1, corner2},
    plots{std::vector<std::vector<SoilStatus>>(std::abs(corner1.y - corner2.y),
        std::vector<SoilStatus>(std::abs(corner1.x - corner2.x), SoilStatus::Fertile))},
    xOffset{std::min(corner1.x, corner2.x)},
    yOffset{std::min(corner1.y, corner2.y)}
{
}

void FarmLand::AddBarrenPlot(const common::Land& plot)
{
    auto plotTop = std::min(plot.Top() - yOffset, Height());
    auto plotBottom = std::max(plot.Bottom() - yOffset, 0);
    auto plotLeft = std::max(plot.Left() - xOffset, 0);
    auto plotRight = std::min(plot.Right() - xOffset, Width());

    for(auto y = plotBottom; y < plotTop; ++y)
    {
        for(auto x = plotLeft; x < plotRight; ++x)
        {
            SetSoilStatus({x,y}, SoilStatus::Infertile);
        }
    }
}

std::vector<size_t> FarmLand::FertilePlots()
{
    auto fertilePlots = std::vector<size_t>{};

    for(int y = 0; y < Height(); ++y)
    {
        for(int x = 0; x < Width(); ++x)
        {
            if(GetSoilStatus({x, y}) == SoilStatus::Fertile)
            {
                auto plotSize = FindSizeOfPlot({x, y});
                fertilePlots.emplace_back(plotSize);
            }
        }
    }

    std::sort(fertilePlots.begin(), fertilePlots.end());

    return fertilePlots;
}

void FarmLand::PrintFarm() const
{
    for(const auto& row : plots)
    {
        for(const auto& p : row)
        {
            std::cout << (p == common::SoilStatus::Fertile) << " ";
        }
        std::cout << "\n";
    }
}

int FarmLand::Width() const
{
    return plots.front().size();
}
int FarmLand::Height() const
{
    return plots.size();
}

bool FarmLand::IsPointInBounds(const Point& loc) const
{
    return loc.x >= 0 && loc.x < Width() && loc.y >= 0 && loc.y < Height();
}

SoilStatus FarmLand::GetSoilStatus(const Point& loc) const
{
    if(IsPointInBounds(loc))
    {
        return plots[loc.y][loc.x];
    }
    return SoilStatus::OutOfBounds;
}

void FarmLand::SetSoilStatus(const Point& loc, SoilStatus status)
{
    if(IsPointInBounds(loc))
    {
        plots[loc.y][loc.x] = status;
    }
}

std::vector<Point> FarmLand::FindSurroudingFertilePoints(const Point& loc)
{
    auto left = Point{loc.x - 1, loc.y};
    auto right = Point{loc.x + 1, loc.y};
    auto down = Point{loc.x, loc.y - 1};
    auto up = Point{loc.x, loc.y + 1};
    auto surroundingPlots = std::vector<Point>{left, right, up, down};
    auto fertilePlots = std::vector<Point>{};
    for (const auto& plot : surroundingPlots)
    {
        if(GetSoilStatus(plot) == SoilStatus::Fertile)
        {
            SetSoilStatus(plot, SoilStatus::Checked);
            fertilePlots.emplace_back(plot);
        }
    }
    return fertilePlots;
}

size_t FarmLand::FindSizeOfPlot(const Point& loc)
{
    auto plotSize = size_t{0};
    if(GetSoilStatus(loc) != SoilStatus::Fertile)
    {
        return plotSize;
    }

    SetSoilStatus(loc, SoilStatus::Checked);
    auto queue = std::queue<Point>{};
    queue.emplace(loc);

    while(!queue.empty())
    {
        auto currentLoc = queue.front();
        queue.pop();
        if(GetSoilStatus(currentLoc) == SoilStatus::Checked)
        {
            ++plotSize;
            auto fertilePlots = FindSurroudingFertilePoints(currentLoc);
            for(const auto& plot : fertilePlots)
            {
                queue.emplace(plot);
            }
        }
    }

    return plotSize;
}
}
