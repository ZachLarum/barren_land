#include "Point.hpp"

std::ostream& operator << (std::ostream& os, const common::Point& p)
{
    return os << "(" << p.x << "," << p.y << ")";
}
