#include "gtest/gtest.h"

#include "InputParser.cpp"
#include <iostream>

TEST(Free, ToInt_ValidIntValue_Converts)
{
    EXPECT_EQ(ToInt("1"), 1);
    EXPECT_EQ(ToInt("0"), 0);
    EXPECT_EQ(ToInt("-1"), -1);
    EXPECT_EQ(ToInt(std::to_string(std::numeric_limits<int>::max())),
            std::numeric_limits<int>::max());
    EXPECT_EQ(ToInt(std::to_string(std::numeric_limits<int>::min())),
            std::numeric_limits<int>::min());
}

TEST(Free, ToInt_OutOfRangeInt_Throws)
{
    EXPECT_THROW({
        long int overflow = std::numeric_limits<int>::max();
        ++overflow;
        try
        {
            ToInt(std::to_string(overflow));
        }
        catch( const ParseException& e )
        {
            std::ostringstream errMsg;
            errMsg << "'" << overflow << "' is out of the range of an int value.\n";
            EXPECT_STREQ(errMsg.str().c_str(), e.what() );
            throw;
        }
    }, ParseException );

    EXPECT_THROW({
        long int overflow = std::numeric_limits<int>::min();
        --overflow;
        try
        {
            ToInt(std::to_string(overflow));
        }
        catch( const ParseException& e )
        {
            std::ostringstream errMsg;
            errMsg << "'" << overflow << "' is out of the range of an int value.\n";
            EXPECT_STREQ(errMsg.str().c_str(), e.what() );
            throw;
        }
    }, ParseException );
}

TEST(Free, ToInt_NonNumericValue_Throws)
{
    auto nonNumericVals =
            std::string{"abcdefghijklmnopqrstuvwxyz.,/<>?+=_-'\";:\\|[]{}!@#$%^&*()"};
    for(auto c : nonNumericVals)
    {
        EXPECT_THROW({
                try
                {
                    ToInt({c});
                }
                catch( const ParseException& e )
                {
                    std::ostringstream errMsg;
                    errMsg << "'" << c << "' could not be converted to an int.\n";
                    EXPECT_STREQ(errMsg.str().c_str(), e.what() );
                    throw;
                }
            }, ParseException );
    }
}

TEST(Free, Split_EmptyString_ReturnsEmptVector)
{
    auto actual = Split("", ' ');
    EXPECT_EQ(actual.size(), 0);
}

TEST(Free, Split_SingleEntry_ReturnsSingleItem)
{
    auto actual = Split("This", ' ');
    ASSERT_EQ(actual.size(), 1);
    EXPECT_EQ(actual.front(), "This");
}

TEST(Free, Split_TwoEntries_ReturnsTwoItems)
{
    auto actual = Split("This is", ' ');
    ASSERT_EQ(actual.size(), 2);
    EXPECT_EQ(actual[0], "This");
    EXPECT_EQ(actual[1], "is");

    actual = Split("This,is", ',');
    ASSERT_EQ(actual.size(), 2);
    EXPECT_EQ(actual[0], "This");
    EXPECT_EQ(actual[1], "is");
}

TEST(Free, Split_TwoEntriesWithEndingDelim_ReturnsTwoItems)
{
    auto actual = Split("This is", ' ');
    ASSERT_EQ(actual.size(), 2);
    EXPECT_EQ(actual[0], "This");
    EXPECT_EQ(actual[1], "is");
}

TEST(Free, Split_TwoEntriesWithBeginingDelim_ReturnsThreeItems)
{
    auto actual = Split(" This is", ' ');
    ASSERT_EQ(actual.size(), 3);
    EXPECT_EQ(actual[0], "");
    EXPECT_EQ(actual[1], "This");
    EXPECT_EQ(actual[2], "is");
}

TEST(Free, StripElem_NoElementsMatch_VectorUnchanged)
{
    auto expected = std::vector<std::string>{"this", "is"};
    StripElem(expected, {""});
    EXPECT_EQ(expected.size(), 2);
}

TEST(Free, StripElem_ElementsMatch_VectorChanged)
{
    auto expected = std::vector<std::string>{"", "this", "", "is", ""};
    StripElem(expected, {""});
    EXPECT_EQ(expected.size(), 2);
}

TEST(Free, VerifyRelativePointLocations_CorrectLocations_Succeeds)
{
    auto bottomLeft = common::Point{1, 1};
    auto topRight = common::Point{2, 2};
    EXPECT_NO_THROW(VerifyRelativePointLocations(bottomLeft, topRight));
}

// todo test for points both below or above available values.

TEST(Free, VerifyRelativePointLocations_ReversedLocations_Throws)
{
    auto bottomLeft = common::Point{1, 1};
    auto topRight = common::Point{2, 2};
    EXPECT_THROW({
       try
       {
           VerifyRelativePointLocations(topRight, bottomLeft);
       }
       catch( const ParseException& e )
       {
           std::ostringstream errMsg;
           errMsg << "Relative point locations are invalid."
                  << " Bottom left: " << topRight
                  << " Top right: "  << bottomLeft << "\n"
                  << " Bottom left x coordinate is greater than or equal to"
                      << " top right x coordinate.\n"
                  << " Bottom left y coordinate is greater than or equal to"
                      << " top right y coordinate.\n";
           EXPECT_STREQ(errMsg.str().c_str(), e.what() );
           throw;
       }
   }, ParseException );
}

TEST(Free, VerifyRelativePointLocations_SameXCoordinate_Throws)
{
    auto bottomLeft = common::Point{1, 1};
    auto topRight = common::Point{1, 2};
    EXPECT_THROW({
       try
       {
           VerifyRelativePointLocations(bottomLeft, topRight);
       }
       catch( const ParseException& e )
       {
           std::ostringstream errMsg;
           errMsg << "Relative point locations are invalid."
                  << " Bottom left: " << bottomLeft
                  << " Top right: "  << topRight << "\n"
                  << " Bottom left x coordinate is greater than or equal to"
                      <<" top right x coordinate.\n";
           EXPECT_STREQ(errMsg.str().c_str(), e.what() );
           throw;
       }
   }, ParseException );
}

TEST(Free, VerifyRelativePointLocations_SameYCoordinate_Throws)
{
    auto bottomLeft = common::Point{1, 1};
    auto topRight = common::Point{2, 1};
    EXPECT_THROW({
       try
       {
           VerifyRelativePointLocations(bottomLeft, topRight);
       }
       catch( const ParseException& e )
       {
           std::ostringstream errMsg;
           errMsg << "Relative point locations are invalid."
                  << " Bottom left: " << bottomLeft
                  << " Top right: "  << topRight << "\n"
                  << " Bottom left y coordinate is greater than or equal to"
                      << " top right y coordinate.\n";
           EXPECT_STREQ(errMsg.str().c_str(), e.what() );
           throw;
       }
   }, ParseException );
}

TEST(Free, ParseLand_CorrectData_ReturnsLand)
{
    auto expected = ParseLand("1 2 3 4");
    EXPECT_EQ(expected.Top(), 4);
    EXPECT_EQ(expected.Bottom(), 2);
    EXPECT_EQ(expected.Left(), 1);
    EXPECT_EQ(expected.Right(), 3);
}

TEST(Free, ParseLand_IllFormattedData_ReturnsLand)
{
    auto expected = ParseLand(" 1   2  3 4    ");
    EXPECT_EQ(expected.Top(), 4);
    EXPECT_EQ(expected.Bottom(), 2);
    EXPECT_EQ(expected.Left(), 1);
    EXPECT_EQ(expected.Right(), 3);
}

TEST(Free, ParseLand_IncorrectNumberOfPoints_Throws)
{
    auto expected = ParseLand("1 2 3 4");
    EXPECT_THROW({
       try
       {
           ParseLand("1 2 3");
       }
       catch( const ParseException& e )
       {
           std::ostringstream errMsg;
           errMsg << "Invalid number of points given. Expected 4, received 3."
                  << " Data received '1 2 3'\n";
           EXPECT_STREQ(errMsg.str().c_str(), e.what() );
           throw;
       }
    }, ParseException );
}

TEST(Free, ParseLands_CorrectData_ReturnsSingleLand)
{
    auto expected = ParseAllLand("1 2 3 4");
    EXPECT_EQ(expected.size(), 1);
}

TEST(Free, ParseLands_CorrectData_ReturnsMultipleLands)
{
    auto expected = ParseAllLand("1 2 3 4,5 6 7 8");
    EXPECT_EQ(expected.size(), 2);
}


