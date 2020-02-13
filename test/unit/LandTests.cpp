#include "gtest/gtest.h"

#define private public
#include "Land.cpp"
#undef private

TEST(Land, Constructor_ValidPoints_ReturnsLand)
{
    auto bottomLeft = common::Point{1, 2};
    auto topRight = common::Point{3, 4};

    auto actual = common::Land{bottomLeft, topRight};
    EXPECT_EQ(actual.Top(), 4);
    EXPECT_EQ(actual.Bottom(), 2);
    EXPECT_EQ(actual.Left(), 1);
    EXPECT_EQ(actual.Right(), 3);

    actual = common::Land{topRight, bottomLeft};
    EXPECT_EQ(actual.Top(), 4);
    EXPECT_EQ(actual.Bottom(), 2);
    EXPECT_EQ(actual.Left(), 1);
    EXPECT_EQ(actual.Right(), 3);
}

TEST(Land, Constructor_SamePoint_Throws)
{
    auto point = common::Point{1, 1};
    EXPECT_THROW({
        try
        {
            common::Land(point, point);
        }
        catch( const ParseException& e )
        {
            std::ostringstream errMsg;
            errMsg << "Invalid points received for the creation of Land:\n"
                   << "Point 1: " << point << ", Point 2: " << point << "\n"
                   << "\tBoth x coordinates are the same.\n"
                   << "\tBoth y coordinates are the same.\n";
            EXPECT_STREQ(errMsg.str().c_str(), e.what() );
            throw;
        }
    }, ParseException );
}

TEST(Land, Constructor_SameXValue_Throws)
{
    auto bottomLeft = common::Point{1, 2};
    auto topRight = common::Point{1, 4};
    EXPECT_THROW({
        try
        {
            common::Land(bottomLeft, topRight);
        }
        catch( const ParseException& e )
        {
            std::ostringstream errMsg;
            errMsg << "Invalid points received for the creation of Land:\n"
                   << "Point 1: " << bottomLeft << ", Point 2: " << topRight << "\n"
                   << "\tBoth x coordinates are the same.\n";
            EXPECT_STREQ(errMsg.str().c_str(), e.what() );
            throw;
        }
    }, ParseException );
}

TEST(Land, Constructor_SameYValue_Throws)
{
    auto bottomLeft = common::Point{1, 2};
    auto topRight = common::Point{3, 2};
    EXPECT_THROW({
        try
        {
            common::Land(bottomLeft, topRight);
        }
        catch( const ParseException& e )
        {
            std::ostringstream errMsg;
            errMsg << "Invalid points received for the creation of Land:\n"
                   << "Point 1: " << bottomLeft << ", Point 2: " << topRight << "\n"
                   << "\tBoth y coordinates are the same.\n";
            EXPECT_STREQ(errMsg.str().c_str(), e.what() );
            throw;
        }
    }, ParseException );
}