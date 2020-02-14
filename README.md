# Barren Land
A case study problem administered by Target.

## Problem
You have a farm of 400m by 600m where coordinates of the field are from (0, 0) to (399, 599). A portion of the farm is barren, and all the barren land is in the form of rectangles. Due to these rectangles of barren land, the remaining area of fertile land is in no particular shape. An area of fertile land is defined as the largest area of land that is not covered by any of the rectangles of barren land.

Read input from STDIN. Print output to STDOUT

Input

You are given a set of rectangles that contain the barren land. These rectangles are defined in a string, which consists of four integers separated by single spaces, with no additional spaces in the string. The first two integers are the coordinates of the bottom left corner in the given rectangle, and the last two integers are the coordinates of the top right corner.

Output

Output all the fertile land area in square meters, sorted from smallest area to greatest, separated by a space.


## Running Barren Land Analysis
    Usage: ./barren-land-calculator [OPTION]...
    Outputs fertile land areas of a farm in ascending order given barren land coordinates.
        -h,--help	Show this help message

    Optional:
        -b,--bottom	Bottom of the farm. Default is 0.
        -t,--top    Top of the farm. Default is 599.
        -l,--left   Left side of the farm. Default is 0.
        -r,--right  Right side of the farm. Default is 399.
        -p,--print  Print a visual representation of the farm where 1
                    is fertile land and 0 is infertile.

### Notes
While the program build framework is CMake, cross-platform compilation is not available yet. It is currently compiled on a linux machine with gcc, g++, cmake, and gtest installed. gtest requires pthread.
