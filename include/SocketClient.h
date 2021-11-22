#ifndef SOCKET_CLIENT_H
#define SOCKET_CLIENT_H

#include "Logger.h"

#include <string>

class SocketClient
{
public:
    SocketClient(const std::string& ipAddress = defaultIpAddress,
        const unsigned port = defaultPort);
    ~SocketClient();

    void shutdown();

private:
    static constexpr unsigned defaultPort = 1337;
    static const std::string defaultIpAddress;

    Logger _logger{ "SocketClient" };
    int _fdSocket = -1;
};

#endif