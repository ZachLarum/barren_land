#ifndef SRC__ARG_PARSE_HPP
#define SRC__ARG_PARSE_HPP

namespace common
{
struct CmdParams
{
    int top{599};
    int bottom{0};
    int left{0};
    int right{399};
    bool printFarm{false};
};

CmdParams ParseArgs(int argc, char ** argv);
}

#endif
