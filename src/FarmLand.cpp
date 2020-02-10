#include "FarmLand.hpp"

#include <queue>
#include <stdexcept>
#include <algorithm>

FarmLand::FarmLand(size_t height, size_t width)
: land{std::vector<std::vector<SoilStatus>>(height, std::vector<SoilStatus>(width, SoilStatus::Fertile))}
{
    if(height == 0 || width == 0)
    {
        throw std::runtime_error(std::string{"Incorrect dimensions entered."
                " Farm must have a height of at least 1 and a width of at least 1."} +
                " Height: " + std::to_string(height) +
                " Width: " + std::to_string(width));
    }
}

void FarmLand::AddBarrenPlot(const Rectangle& plot)
{
    auto plotTop = std::min(plot.Top(), Height() - 1);
    auto plotBottom = std::max(plot.Bottom(), 0);
    auto plotLeft = std::max(plot.Left(), 0);
    auto plotRight = std::min(plot.Right(), Width() - 1);

    for(auto y = plotBottom; y <= plotTop; ++y)
    {
        for(auto x = plotLeft; x <= plotRight; ++x)
        {
            land[y][x] = SoilStatus::Infertile;
        }
    }
};


std::vector<size_t> FarmLand::FertilePlots()
{
    auto fertilePlots = std::vector<size_t>{};

    for(size_t y = 0; y < Height(); ++y)
    {
        for(size_t x = 0; x < Width(); ++x)
        {
            if(land[y][x] == SoilStatus::Fertile)
            {
                auto plotSize = FindSizeOfPlot(Point{static_cast<int>(x), static_cast<int>(y)});
                fertilePlots.emplace_back(plotSize);
            }
        }
    }

    std::sort(fertilePlots.begin(), fertilePlots.end());

    return fertilePlots;
}

std::vector<std::vector<SoilStatus>> FarmLand::Land() const
{
    return land;
}

int FarmLand::Width() const
{
    return land.front().size();
}
int FarmLand::Height() const
{
    return land.size();
}

bool FarmLand::IsPointInBounds(const Point& loc)
{
    return loc.x >= 0 && loc.x < Width() && loc.y >= 0 && loc.y < Height();
}

SoilStatus FarmLand::GetSoilStatus(const Point& loc)
{
    if(IsPointInBounds(loc))
    {
        return land[loc.y][loc.x];
    }
    return SoilStatus::OutOfBounds;
}

void FarmLand::SetSoilStatus(const Point& loc, SoilStatus status)
{
    if(IsPointInBounds(loc))
    {
        land[loc.y][loc.x] = status;
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
    auto queue = std::queue<Point>{};

    queue.emplace(loc);

    while(!queue.empty())
    {
        auto currentLoc = queue.front();
        queue.pop();
        auto fertilePlots = FindSurroudingFertilePoints(currentLoc);

        plotSize += fertilePlots.size();

        for(const auto& plot : fertilePlots)
        {
            queue.emplace(plot);
        }
    }

    return plotSize;

}
