#ifndef SOCKET_CLIENT_H
#define SOCKET_CLIENT_H

#include "Logger.h"

#include <poll.h>
#include <string>

class DataTransferObject
{
public:
    DataTransferObject(double xl, double zl, double yr)
    : _xl{ xl }, _zl{ zl }, _yr{ yr } {}

    std::size_t getSerialDataSize() const noexcept
        { return (3 * sizeof(double)); }

    double getXl() const noexcept { return _xl; }
    double getZl() const noexcept { return _zl; }
    double getYr() const noexcept { return _yr; }

private:
    double _xl;
    double _zl;
    double _yr;
};

class SocketClient
{
public:
    ~SocketClient();

    void connect(const std::string& ipAddress = defaultIpAddress,
        const unsigned port = defaultPort);
    void close();

    bool isOperational() const;

    void enableServerWait(const bool enabled = false);
    bool serverWaitEnabled() const;

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
    pollfd _fdMonitor{ -1, POLLIN, 0 };
    bool _operational = false;
    bool _shutdownRequested = false;
    bool _serverWait = false;

    std::vector<DataTransferObject> _dataQueue;
};

#endif