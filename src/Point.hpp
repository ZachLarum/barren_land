#ifndef SRC__POINT_HPP
#define SRC__POINT_HPP

#include <string>

struct Point
{
    std::string ToString() const;

    int x;
    int y;
};

#endif