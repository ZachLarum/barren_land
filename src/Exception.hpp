#ifndef SRC__EXCEPTION_HPP
#define SRC__EXCEPTION_HPP

#include <exception>
#include <string>

class ParseException : public std::exception {

public:
    ParseException(std::string i, std::string fl, std::string fn, int l)
    : info (i),
      file (fl),
      func (fn),
      line (std::to_string(l))
    {
    }

    virtual const char* what() const noexcept
    {
        return info.c_str();
    }

    virtual std::string where() const
    {
        return file + " : " + line + " : " + func;
    }

private:
    std::string info;
    std::string func;
    std::string file;
    std::string line;
};

#define Exception(msg) ParseException { msg, __FILE__, __FUNCTION__, __LINE__ }

#endif