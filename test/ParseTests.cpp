#include "gtest/gtest.h"

#include "Parse.cpp"

#include <limits>
#include <sstream>
#include <string>

TEST(Free, ToInt_ValidIntValue_Converts)
{
    EXPECT_EQ(common::ToInt("1"), 1);
    EXPECT_EQ(common::ToInt("0"), 0);
    EXPECT_EQ(common::ToInt("-1"), -1);
    EXPECT_EQ(common::ToInt(std::to_string(std::numeric_limits<int>::max())),
            std::numeric_limits<int>::max());
    EXPECT_EQ(common::ToInt(std::to_string(std::numeric_limits<int>::min())),
            std::numeric_limits<int>::min());
}

TEST(Free, ToInt_OutOfRangeInt_Throws)
{
    EXPECT_THROW({
        long int overflow = std::numeric_limits<int>::max();
        ++overflow;
        try
        {
            common::ToInt(std::to_string(overflow));
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
            common::ToInt(std::to_string(overflow));
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
                    common::ToInt({c});
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
