#include "InputParser.hpp"
#include "Point.hpp"
#include "Rectangle.hpp"

#include <iostream>
#include <iterator>
#include <vector>
#include <sstream>
#include <cmath>
#include <queue>

// Questions
// If I enter 5 5 5 5, does that mean 1 plot is infertile?

namespace
{
void PrintPoint(const Point& c)
{
    std::cout << c.ToString() << std::endl;
}

void PrintRectangle(const Rectangle& r)
{
    std::cout << "Top: " << r.Top() << ", Bottom: " << r.Bottom() << ", Left: " << r.Left() << ", Right: " << r.Right() << std::endl;
}



void PromptUser()
{
    std::cout << "Enter barren plots" << std::endl;
}

enum class SoilStatus
{
    OutOfBounds,
    Fertile,
    Checked,
    Infertile,
};

}

class FarmingLand
{
public:
    FarmingLand(size_t height, size_t width)
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

    void AddBarrenPlot(const Rectangle& plot)
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


    std::vector<size_t> FertilePlots()
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

        return fertilePlots;
    }

    std::vector<std::vector<SoilStatus>> Land() const
    {
        return land;
    }

private:
    int Width()
    {
        return land.front().size();
    }
    int Height()
    {
        return land.size();
    }

    bool IsPointInBounds(const Point& loc)
    {
        return loc.x >= 0 && loc.x < Width() && loc.y >= 0 && loc.y < Height();
    }

    SoilStatus GetSoilStatus(const Point& loc)
    {
        if(IsPointInBounds(loc))
        {
            return land[loc.y][loc.x];
        }
        return SoilStatus::OutOfBounds;
    }

    void SetSoilStatus(const Point& loc, SoilStatus status)
    {
        if(IsPointInBounds(loc))
        {
            land[loc.y][loc.x] = status;
        }
    }

    std::vector<Point> FindSurroudingFertilePoints(const Point& loc)
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

    size_t FindSizeOfPlot(const Point& loc)
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



    std::vector<std::vector<SoilStatus>> land;
};

void PrintFarm(const FarmingLand& land)
{
    auto l =  land.Land();
    for(auto& col : l)
    {
        for(auto& row : col)
        {
            std::cout << (row == SoilStatus::Fertile) << " ";
        }
        std::cout << "\n";
    }
}

int main()
{
    PromptUser();
    auto barrenPlots = parse::ParseInput();

//    for(const auto& p : barrenPlots)
//    {
//        PrintRectangle(p);
//    }

    auto farm = FarmingLand(10, 10);

    for(const auto& plot : barrenPlots)
    {
        farm.AddBarrenPlot(plot);
    }
    PrintFarm(farm);
    auto plots = farm.FertilePlots();

    std::cout << "Fertile plots " << std::endl;
    for (const auto& plot : plots)
    {
        std::cout << "\t" << plot << std::endl;
    }


}