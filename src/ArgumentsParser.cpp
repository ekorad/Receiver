#include "ArgumentsParser.h"
#include <stdexcept>
#include <unistd.h>
#include <arpa/inet.h>

ArgumentsParser::ArgumentsParser(const int argc, char* const argv[])
{
    char opt;

    opterr = 0;

    while ((opt = getopt(argc, argv, optString.c_str())) != -1)
    {
        switch (opt)
        {
            case 'd':
                _debug = true;
                break;
            case 'n':
                if (optarg)
                {
                    _samples = std::stoull(optarg);
                }
                break;
            case 'p':
                if (optarg)
                {
                    _port = std::stoi(optarg);
                }
                break;
            case 'i':
                if (optarg)
                {
                    parseIPAddress(optarg);
                }
                break;
            case '?':
                handleOptionError(optopt);
        }
    }
}

void ArgumentsParser::handleOptionError(const int opt) const
{
    switch (opt)
    {
        case 'n':
            throw std::runtime_error("Option -n requires a valid number of samples");
        case 'p':
            throw std::runtime_error("Option -p requires a valid port number");
        case 'i':
            throw std::runtime_error("Option -i requires a valid IP address");
        default:
            if (std::isprint(opt))
            {
                throw std::runtime_error("Invalid option: -" + static_cast<char>(opt));
            }
            else
            {
                throw std::runtime_error("Invalid option character: " + opt);
            }
    }
}

void ArgumentsParser::parseIPAddress(const char* addr)
{
    if (inet_addr(addr) == -1)
    {
        throw std::runtime_error("Invalid IP address");
    }
    _addr = std::string{ addr };
}

const std::string ArgumentsParser::optString = "dn:p:i:";
const std::string ArgumentsParser::defAddr = "127.0.0.1";