#include "FarmLand.hpp"
#include "InputParser.hpp"
#include "Point.hpp"
#include <iostream>
#include <iterator>
#include <vector>
#include "Land.hpp"

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
void PrintFarm(const common::FarmLand& land)
{
    auto l =  land.Land();
    for(auto& col : l)
    {
        for(auto& row : col)
        {
            std::cout << (row == common::SoilStatus::Fertile) << " ";
        }
        std::cout << "\n";
    }
}
}

int main()
{
    PromptUser();

    // TODO Catch exceptions, display message, and reprompt.
    auto barrenPlots = common::ParseInput();
    auto farm = common::FarmLand(common::Point{0,0}, common::Point{10, 10});

    for(const auto& plot : barrenPlots)
    {
        farm.AddBarrenPlot(plot);
    }

    PrintFarm(farm);
    auto plots = farm.FertilePlots();

    PrintPlots(plots);
}