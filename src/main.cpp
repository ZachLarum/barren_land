#include "ArgParse.hpp"
#include "Exception.hpp"
#include "FarmLand.hpp"
#include "InputParser.hpp"
#include "Land.hpp"
#include "Point.hpp"

#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>


namespace
{
void DisplayHelpMessage()
{
    std::cout << "Plots must consist of four integeres separated by a space.\n"
              << "The first pair corresponds to the bottom left of the plot.\n"
              << "The second pair corresponds to the top right of the plot.\n"
              << "Each plot must be separated by a comma.\n"
              << "Example\n"
              << "\t1 2 6 8, 0 0 5 6\n"
              << "Press Enter when all points have been inputed.\n\n";
}

std::vector<common::Land> PromptUser()
{
    std::cout << "Enter barren plots" << "\n\n";

    auto userInputUnsuccessful = true;
    auto barrenPlots = std::vector<common::Land>{};

    while(userInputUnsuccessful)
    {
        try
        {
            barrenPlots = common::ParseInput();
            userInputUnsuccessful = false;
        }
        catch (const ParseException& e)
        {
            std::cout << "\n--------Input Invalid--------\n" << e.what() << "\n";
            DisplayHelpMessage();
        }
        }
    return barrenPlots;
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
}

int main(int argc, char** argv)
{
    auto params = common::ParseArgs(argc, argv);

    auto farm = common::FarmLand(
        common::Point{params.left, params.bottom},
        common::Point{params.right, params.top});

    auto barrenPlots = PromptUser();

    for(const auto& plot : barrenPlots)
    {
        farm.AddBarrenPlot(plot);
    }
    if (params.printFarm)
    {
        farm.PrintFarm();
    }
    auto plots = farm.FertilePlots();
    PrintPlots(plots);
}