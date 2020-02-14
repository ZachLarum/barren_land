#include "ArgParse.hpp"

#include "Exception.hpp"
#include "Parse.hpp"

#include <getopt.h>
#include <iostream>
#include <sstream>
#include <vector>

namespace {
static void Usage(const std::string & name)
{
    std::cout << "Usage: " << name << " [OPTION]...\n"
        << "Outputs fertile land areas of a farm in ascending order given barren\n"
        << "land coordinates."
        << "\n\t-h,--help\tShow this help message\n"
        << "\nOptional:\n"
        << "\t-b,--bottom\tBottom of the farm. Default is 0.\n"
        << "\t-t,--top\tTop of the farm. Default is 599.\n"
        << "\t-l,--left\tLeft side of the farm. Default is 0.\n"
        << "\t-r,--right\tRight side of the farm. Default is 399.\n"
        << "\t-p,--print\tPrint a visual representation of the farm where 1\n"
            << "\t\t\tis fertile land and 0 is infertile.\n"
        << "\n";
}

std::vector<option> BuildOpts()
{
    return {{"help", no_argument, NULL, 'h'},
            {"bottom", required_argument, NULL, 'b'},
            {"top", required_argument, NULL, 't'},
            {"left", required_argument, NULL, 'l'},
            {"right", required_argument, NULL, 'r'},
            {"print", no_argument, NULL, 'p'},
            {NULL, 0, NULL, 0},};
}

void ValidateArgs(const common::CmdParams& params)
{
    if (params.bottom >= params.top || params.left >= params.right)
    {
        std::ostringstream errMsg;
        errMsg << "Please enter valid dimensions for the farm.\n";
        if(params.bottom >= params.top)
        {
            errMsg << "The bottom of the farm must be less than the top value.\n"
                   << "bottom: " << params.bottom << ", top: " << params.top << "\n";
        }
        if(params.left >= params.right)
        {
            errMsg << "The left value of the farm must be less than the right value.\n"
                   << "left: " << params.left << ", right: " << params.right << "\n";
        }
        std::cerr << errMsg.str() << std::endl;
        exit(1);
    }
}
}

namespace common
{
CmdParams ParseArgs(int argc, char ** argv)
{
    const auto longOpts = BuildOpts();

    // suppress getopt_long_only() stderr messages.
    opterr = 0;

    auto showUsage = false;

    CmdParams params{};
    int c = 0;
    while ((c = getopt_long(argc, argv, "hb:t:l:r:p", longOpts.data(), NULL)) != -1)
    {
        switch (c)
        {
        case 'h':
            Usage(argv[0]);
            exit(0);
        case 'b':
            params.bottom = ToInt(optarg);
            break;
        case 't':
            params.top = ToInt(optarg);
            break;
        case 'l':
            params.left = ToInt(optarg);
            break;
        case 'r':
            params.right = ToInt(optarg);
            break;
        case 'p':
            params.printFarm = true;
            break;
        case '?':
            showUsage = true;
            break;
        default:
            std::cerr << argv[0] << ": unknown option -- '"
            << static_cast<char>(c) << "'" << "\n";
            showUsage = true;
            break;
        }
    }

    ValidateArgs(params);

    // If an invalid or missing parameter occurs show usage and exit.
    if (showUsage)
    {
        Usage(argv[0]);
        exit(2);
    }

    return params;
}
}