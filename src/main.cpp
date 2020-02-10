#include "FarmLand.hpp"
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
void PromptUser()
{
    std::cout << "Enter barren plots" << std::endl;
}

void PrintPlots(const std::vector<size_t>& plots)
{
    std::cout << "Fertile plots " << std::endl;
    for (const auto& plot : plots)
    {
        std::cout << plot << " ";
    }
    std::cout << std::endl;
}


// TODO remove
void PrintFarm(const FarmLand& land)
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
}


int main()
{
    PromptUser();

    auto barrenPlots = parse::ParseInput();
    auto farm = FarmLand(10, 10);

    for(const auto& plot : barrenPlots)
    {
        farm.AddBarrenPlot(plot);
    }

    PrintFarm(farm);
    auto plots = farm.FertilePlots();

    PrintPlots(plots);
}