#include "Point.hpp"

#include <sstream>
// TODO remove file
std::string Point::ToString() const
{
    std::ostringstream oss;
    oss << "(" << x << ", " << y << ")";
    return oss.str();
}
