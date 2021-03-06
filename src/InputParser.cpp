#include "InputParser.hpp"

#include "Exception.hpp"
#include "Land.hpp"
#include "Parse.hpp"
#include "Point.hpp"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

namespace
{
template<typename T>
void StripElem(std::vector<T>& container, T item)
{
    container.erase(std::remove(container.begin(), container.end(), item), container.end());
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
    if(bottomLeft.x >= topRight.x || bottomLeft.y >= topRight.y)
    {
        std::ostringstream errMsg;
        errMsg << "Relative point locations are invalid."
               << " Bottom left: " << bottomLeft
               << " Top right: "  << topRight << "\n";
        if(bottomLeft.x >= topRight.x)
        {
            errMsg  << " Bottom left x coordinate is greater than or equal to top right x coordinate.\n";
        }
        if(bottomLeft.y >= topRight.y)
        {
            errMsg << " Bottom left y coordinate is greater than or equal to top right y coordinate.\n";
        }
        throw Exception(errMsg.str());
    }
}

common::Land ParseLand(const std::string& data)
{
    auto coordinates = Split(data, ' ');\
    StripElem(coordinates, {""});
    if(coordinates.size() % 4 != 0)
    {
        std::ostringstream errMsg;
        errMsg << "Invalid number of points given. Expected 4, received "
               << coordinates.size() << ". Data received '" << data << "'\n";
        throw Exception(errMsg.str());
    }
    auto bottomLeft = common::Point{common::ToInt(coordinates[0]), common::ToInt(coordinates[1])};
    auto topRight = common::Point{common::ToInt(coordinates[2]), common::ToInt(coordinates[3])};
    VerifyRelativePointLocations(bottomLeft, topRight);
    return {bottomLeft, topRight};
}

std::vector<common::Land> ParseAllLand(const std::string& data)
{
    auto plotStrings = Split(data, ',');

    std::vector<common::Land> rec{};
    for(const auto& p : plotStrings)
    {
        rec.emplace_back(ParseLand(p));
    }

    return rec;
}
}

namespace common
{
std::vector<Land> ParseInput()
{
    std::string answer;
    std::getline(std::cin, answer);

    return ParseAllLand(answer);
}
}