#include "Rectangle.hpp"
#include "Exception.hpp"

#include <sstream>

namespace common
{
Rectangle::Rectangle(Point corner1, Point corner2)
: top{FindTop(corner1.y, corner2.y)},
  bottom{FindBottom(corner1.y, corner2.y)},
  right{FindRight(corner1.x, corner2.x)},
  left{FindLeft(corner1.x, corner2.x)}
{
    if(top == bottom || right == left)
    {
        std::ostringstream errMsg;
        errMsg << "Invalid points received for a Rectangle:\n"
               << "Point 1: " << corner1 << ", Point 2: " << corner2 << "\n";
        if (right == left)
        {
            errMsg << "\tBoth x coordinates are the same.\n";
        }
        if (top == bottom)
        {
            errMsg << "\tBoth y coordinates are the same.\n";
        }
        throw Exception(errMsg.str());
    }
}

int Rectangle::Top() const
{
    return top;
}

int Rectangle::Bottom() const
{
    return bottom;
}

int Rectangle::Left() const
{
    return left;
}

int Rectangle::Right() const
{
    return right;
}

int Rectangle::Area() const
{
    return (Top() - Bottom()) * (Right() - Left());
}

int Rectangle::FindBottom(int x1, int x2)
{
    return std::min(x1, x2);
}

int Rectangle::FindTop(int x1, int x2)
{
    return std::max(x1, x2);
}

int Rectangle::FindRight(int y1, int y2)
{
    return std::max(y1, y2);
}

int Rectangle::FindLeft(int y1, int y2)
{
    return std::min(y1, y2);
}
}

