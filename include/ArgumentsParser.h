#ifndef ARGUMENTS_PARSER_H
#define ARGUMENTS_PARSER_H

#include <string>

class ArgumentsParser
{
public:
    ArgumentsParser(const int argc, char* const argv[]);

    unsigned getPort() const noexcept { return _port; }
    unsigned long long getSampleCount() const noexcept { return _samples; }
    std::string getIPAddress() const noexcept { return _addr; }
    bool debugEnabled() const noexcept { return _debug; }

private:
    static constexpr unsigned defPort = 1337;
    static constexpr unsigned long long maxSamples = 5000001;
    static const std::string defAddr;
    static const std::string optString;

    void handleOptionError(const int opt) const;
    void parseIPAddress(const char* addr);

    unsigned _port = defPort;
    unsigned long long _samples = maxSamples;
    bool _debug = false;
    std::string _addr = defAddr;
};

#endif