#ifndef SRC__POINT_HPP
#define SRC__POINT_HPP

#include <string>

namespace common
{
struct Point final
{
    int x;
    int y;
};
}

std::ostream& operator << (std::ostream& os, const common::Point& p);

#endif