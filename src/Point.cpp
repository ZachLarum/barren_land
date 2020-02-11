#include "Point.hpp"

#include <sstream>

std::ostream& operator << (std::ostream& os, const common::Point& p)
{
    return os << "(" << p.x << "," << p.y << ")";
}
