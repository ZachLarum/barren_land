#ifndef SRC__FARM_LAND_HPP
#define SRC__FARM_LAND_HPP

#include "Land.hpp"
#include "Point.hpp"
#include <string>
#include <vector>

namespace common
{
enum class SoilStatus
{
    OutOfBounds,
    Fertile,
    Checked,
    Infertile,
};

class FarmLand : public Land
{
public:
    FarmLand(Point corner1, Point corner2);

    void AddBarrenPlot(const Land& plot);

    std::vector<size_t> FertilePlots();

    void PrintFarm() const;
private:
    int Height() const;
    int Width() const;

    bool IsPointInBounds(const Point& loc) const;

    SoilStatus GetSoilStatus(const Point& loc) const;
    void SetSoilStatus(const Point& loc, SoilStatus status);

    size_t FindSizeOfPlot(const Point& loc);

    std::vector<Point> FindSurroudingFertilePoints(const Point& loc);

    std::vector<std::vector<SoilStatus>> plots;
    int xOffset;
    int yOffset;
};
}

#endif