#include "Parse.hpp"

#include "Exception.hpp"

#include <sstream>
#include <stdexcept>

namespace common
{
int ToInt(const std::string& s)
{
    try
    {
        return std::stoi(s);
    }
    catch (const std::invalid_argument& e)
    {
        std::ostringstream errMsg;
        errMsg << "'" << s << "' could not be converted to an int.\n";
        throw Exception(errMsg.str());
    }
    catch (const std::out_of_range& e)
    {
        std::ostringstream errMsg;
        errMsg << "'" << s << "' is out of the range of an int value.\n";
        throw Exception(errMsg.str());
    }
}
}