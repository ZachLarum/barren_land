#ifndef SRC__LAND_HPP
#define SRC__LAND_HPP

#include "Point.hpp"

namespace common
{
class Land
{
public:
    Land(Point corner1, Point corner2);

    int Top() const;
    int Bottom() const;
    int Left() const;
    int Right() const;

    int Area() const;
private:
    int FindTop(int x1, int x2);
    int FindBottom(int x1, int x2);
    int FindLeft(int y1, int y2);
    int FindRight(int y1, int y2);

    int top;
    int bottom;
    int left;
    int right;
};
}

#endif

