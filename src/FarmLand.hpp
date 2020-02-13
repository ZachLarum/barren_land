#ifndef SRC__FARM_LAND_HPP
#define SRC__FARM_LAND_HPP

#include "Point.hpp"
#include "Rectangle.hpp"

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

class FarmLand : public Rectangle
{
public:
    FarmLand(Point corner1, Point corner2);

    void AddBarrenPlot(const common::Rectangle& plot);

    std::vector<size_t> FertilePlots();

    std::vector<std::vector<SoilStatus>> Land() const;
private:
    int Height() const;
    int Width() const;

    bool IsPointInBounds(const common::Point& loc) const;

    SoilStatus GetSoilStatus(const common::Point& loc) const;
    void SetSoilStatus(const common::Point& loc, SoilStatus status);

    size_t FindSizeOfPlot(const common::Point& loc);

    std::vector<common::Point> FindSurroudingFertilePoints(const common::Point& loc);

    std::vector<std::vector<SoilStatus>> land;
    int xOffset;
    int yOffset;
};
}

#endif