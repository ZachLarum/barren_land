#include "InputParser.hpp"
#include "Point.hpp"
#include "Rectangle.hpp"

#include <iostream>
#include <iterator>
#include <sstream>
#include <string>

namespace
{
int ToInt(const std::string& s)
{
    try
    {
        return std::stoi(s);
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << "'" << s << "' could not be converted to an int.\n";
        throw e;
    }
    catch (const std::out_of_range& e)
    {
        std::cerr << "'" << s << "' is greater than the int max value.\n";
        throw e;
    }
}

std::vector<std::string> Split(const std::string& s, char delim)
{
   std::istringstream stream(s);
   auto item = std::string{};
   auto res = std::vector<std::string>{};
   while (std::getline(stream, item, delim))
   {
      res.emplace_back(item);
   }
   return res;
}

void VerifyRelativePointLocations(const common::Point& bottomLeft, const common::Point& topRight)
{
    if(bottomLeft.x >= topRight.x)
    {
        std::ostringstream errMsg;
        errMsg << "Relative point locations are invalid."
               << " Bottom left x coordinate is greater than than top right x coordinate.\n"
               << " Bottom left: " << bottomLeft
               << " Top right: "  << topRight << "\n";
        throw std::runtime_error(errMsg.str());
    }
    if(bottomLeft.y >= topRight.y)
    {
        std::ostringstream errMsg;
        errMsg << "Relative point locations are invalid."
               << " Bottom left y coordinate is greater than than top right y coordinate.\n"
               << " Bottom left: " << bottomLeft
               << " Top right: " << topRight << "\n";
        throw std::runtime_error(errMsg.str());
    }
}

common::Rectangle ParseRectangle(const std::string& data)
{
    auto coordinates = Split(data, ' ');
    if(coordinates.size() % 4 != 0)
    {
        // todo make more explicit
        throw std::runtime_error(std::string{"Invalid number of points given. Expected 4, received "} +
                std::to_string(coordinates.size()) + ". Points data received '" + data + "'");
    }
    auto bottomLeft = common::Point{ToInt(coordinates[0]), ToInt(coordinates[1])};
    auto topRight = common::Point{ToInt(coordinates[2]), ToInt(coordinates[3])};
    VerifyRelativePointLocations(bottomLeft, topRight);
    return {bottomLeft, topRight};
}

std::vector<common::Rectangle> ParseRectangles(const std::string& data)
{
    auto plotStrings = Split(data, ',');

    std::vector<common::Rectangle> rec{};
    for(const auto& p : plotStrings)
    {
        rec.emplace_back(ParseRectangle(p));
    }

    return rec;
}
}

namespace common
{
std::vector<Rectangle> ParseInput()
{
    std::string answer;
    std::getline(std::cin, answer);

    return ParseRectangles(answer);
}
}