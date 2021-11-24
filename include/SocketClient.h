#ifndef SOCKET_CLIENT_H
#define SOCKET_CLIENT_H

#include "Logger.h"

#include <string>

class SocketClient
{
public:
    ~SocketClient();

    void connect(const std::string& ipAddress = defaultIpAddress,
        const unsigned port = defaultPort);
    void close();

    bool isOperational() const;

private:
    static constexpr unsigned defaultPort = 1337;
    static const std::string defaultIpAddress;

    void shutdown(const bool omitExtraLogs = false);
    void stopThread();
    void clientThreadFunc();

    std::optional<std::thread> _clientThread;
    mutable std::mutex _mutex;
    std::condition_variable _condVar;

    Logger _logger{ "SocketClient" };

    int _fdSocket = -1;
    bool _operational = false;
    bool _shutdownRequested = false;
};

#endif