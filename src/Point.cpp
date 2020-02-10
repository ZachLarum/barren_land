#include "Point.hpp"

#include <sstream>

std::string Point::ToString() const
{
    std::ostringstream oss;
    oss << "(" << x << ", " << y << ")";
    return oss.str();
}
