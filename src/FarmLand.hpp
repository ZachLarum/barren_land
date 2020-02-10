#ifndef SRC__FARM_LAND_HPP
#define SRC__FARM_LAND_HPP

#include "Point.hpp"
#include "Rectangle.hpp"

#include <string>
#include <vector>

enum class SoilStatus
{
    OutOfBounds,
    Fertile,
    Checked,
    Infertile,
};

class FarmLand
{
public:
    FarmLand(size_t height, size_t width);

    void AddBarrenPlot(const Rectangle& plot);

    std::vector<size_t> FertilePlots();

    std::vector<std::vector<SoilStatus>> Land() const;

private:
    int Height() const;

    int Width() const;

    bool IsPointInBounds(const Point& loc);

    SoilStatus GetSoilStatus(const Point& loc);

    void SetSoilStatus(const Point& loc, SoilStatus status);

    std::vector<Point> FindSurroudingFertilePoints(const Point& loc);

    size_t FindSizeOfPlot(const Point& loc);

    std::vector<std::vector<SoilStatus>> land;
};

#endif