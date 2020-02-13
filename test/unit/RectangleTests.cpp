#include "gtest/gtest.h"

#define private public
#include "Rectangle.cpp"
#undef private

TEST(Rectangle, Constructor_ValidPoints_ReturnsRectangle)
{
    auto bottomLeft = common::Point{1, 2};
    auto topRight = common::Point{3, 4};

    auto actual = common::Rectangle{bottomLeft, topRight};
    EXPECT_EQ(actual.Top(), 4);
    EXPECT_EQ(actual.Bottom(), 2);
    EXPECT_EQ(actual.Left(), 1);
    EXPECT_EQ(actual.Right(), 3);

    actual = common::Rectangle{topRight, bottomLeft};
    EXPECT_EQ(actual.Top(), 4);
    EXPECT_EQ(actual.Bottom(), 2);
    EXPECT_EQ(actual.Left(), 1);
    EXPECT_EQ(actual.Right(), 3);
}

TEST(Rectangle, Constructor_SamePoint_Throws)
{
    auto point = common::Point{1, 1};
    EXPECT_THROW({
        try
        {
            common::Rectangle(point, point);
        }
        catch( const ParseException& e )
        {
            std::ostringstream errMsg;
            errMsg << "Invalid points received for a Rectangle:\n"
                   << "Point 1: " << point << ", Point 2: " << point << "\n"
                   << "\tBoth x coordinates are the same.\n"
                   << "\tBoth y coordinates are the same.\n";
            EXPECT_STREQ(errMsg.str().c_str(), e.what() );
            throw;
        }
    }, ParseException );
}

TEST(Rectangle, Constructor_SameXValue_Throws)
{
    auto bottomLeft = common::Point{1, 2};
    auto topRight = common::Point{1, 4};
    EXPECT_THROW({
        try
        {
            common::Rectangle(bottomLeft, topRight);
        }
        catch( const ParseException& e )
        {
            std::ostringstream errMsg;
            errMsg << "Invalid points received for a Rectangle:\n"
                   << "Point 1: " << bottomLeft << ", Point 2: " << topRight << "\n"
                   << "\tBoth x coordinates are the same.\n";
            EXPECT_STREQ(errMsg.str().c_str(), e.what() );
            throw;
        }
    }, ParseException );
}

TEST(Rectangle, Constructor_SameYValue_Throws)
{
    auto bottomLeft = common::Point{1, 2};
    auto topRight = common::Point{3, 2};
    EXPECT_THROW({
        try
        {
            common::Rectangle(bottomLeft, topRight);
        }
        catch( const ParseException& e )
        {
            std::ostringstream errMsg;
            errMsg << "Invalid points received for a Rectangle:\n"
                   << "Point 1: " << bottomLeft << ", Point 2: " << topRight << "\n"
                   << "\tBoth y coordinates are the same.\n";
            EXPECT_STREQ(errMsg.str().c_str(), e.what() );
            throw;
        }
    }, ParseException );
}