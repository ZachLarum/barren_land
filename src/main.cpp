#include "InputParser.hpp"
#include "Point.hpp"
#include "Rectangle.hpp"

#include <iostream>
#include <iterator>
#include <vector>
#include <sstream>
#include <cmath>

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
}

class FarmingLand
{
public:
    FarmingLand(size_t height, size_t width)
    : land{std::vector<std::vector<int>>(height, std::vector<int>(width, 1))}
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
                land[y][x] = 0;
            }
        }
    };

    std::vector<std::vector<int>> Land() const
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
    std::vector<std::vector<int>> land;
};

void PrintFarm(const FarmingLand& land)
{
    auto l =  land.Land();
    for(auto& col : l)
    {
        for(auto& row : col)
        {
            std::cout << row << " ";
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


}