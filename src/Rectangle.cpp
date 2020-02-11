#include "Rectangle.hpp"


namespace common
{
Rectangle::Rectangle(Point corner1, Point corner2)
: top{FindTop(corner1.y, corner2.y)},
  bottom{FindBottom(corner1.y, corner2.y)},
  right{FindRight(corner1.x, corner2.x)},
  left{FindLeft(corner1.x, corner2.x)}
{
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

