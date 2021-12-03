#include "SocketClient.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <poll.h>
#include <cstring>

void SocketClient::connect(const std::string& ipAddress, const unsigned port)
{
    std::unique_lock<std::mutex> lock{ _mutex };
    if (_fdSocket != -1)
    {
        const std::runtime_error error{ "Already connected to server" };
        _logger.log(error.what(), LoggingLevel::ERROR);
        throw error;
    }

    _fdSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (_fdSocket == -1)
    {
        const std::system_error error{ errno, std::system_category(),
            "Could not create endpoint socket" };
        _logger.log(error.what(), LoggingLevel::ERROR);
        throw error;
    }
    else
    {
        _logger.log("Initialized endpoint socket with descriptor: "
        + std::to_string(_fdSocket));
    }

    sockaddr_in addrServer;
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(port);

    if (inet_pton(AF_INET, ipAddress.c_str(), &addrServer.sin_addr) <= 0) 
    {
        const std::system_error error{ errno, std::system_category(),
            "Could not convert IP address string " + ipAddress
            + " to binary form" };
        _logger.log(error.what(), LoggingLevel::ERROR);
        lock.unlock();
        shutdown();
        throw error;
    }

    _logger.log("Attempting connection to server with IP address "
        + ipAddress + " on port " + std::to_string(port) + "...");

    if (::connect(_fdSocket, (struct sockaddr *)&addrServer, sizeof(addrServer))
        == -1)
    {
        const std::system_error error{ errno, std::system_category(),
            "Could not connect to server" };
        _logger.log(error.what(), LoggingLevel::ERROR);
        lock.unlock();
        shutdown();
        throw error;
    }
    else
    {
        _logger.log("Successfully established connection to server",
            LoggingLevel::INFO);
    }
    // _logger.log("Skipped connection to server (debug)!", LoggingLevel::WARNING);

    try
    {
        _clientThread = std::thread{ &SocketClient::clientThreadFunc, this };
        _operational = true;
    }
    catch(const std::system_error& error)
    {
        const std::system_error thrownError{ error.code().value(),
            std::system_category(), "Could not start client thread" };
        _logger.log(thrownError.what(), LoggingLevel::ERROR);
        lock.unlock();
        shutdown();
        throw thrownError;
    }

    _fdMonitor.fd = _fdSocket;

    _logger.log("Monitoring event " + std::to_string(_fdMonitor.events)
        + " for socket descriptor");

    _logger.log("Socket client operational", LoggingLevel::INFO);
}

SocketClient::~SocketClient()
{
    shutdown(true);

    _logger.log("Destroyed socket client", LoggingLevel::INFO);
}

void SocketClient::shutdown(const bool omitExtraLogs)
{
    if (!omitExtraLogs)
    {
        _logger.log("Shutdown has been requested, commencing...");
    }

    std::unique_lock<std::mutex> lock{ _mutex };
    if ((_fdSocket == -1) && !omitExtraLogs)
    {
        _logger.log("Socket descriptor is not initialized");
        return;
    }

    if (_operational)
    {
        _operational = false;
        _logger.log("Client is no longer operational, requesting client thread"
            " shutdown...");
        _shutdownRequested = true;
        lock.unlock();
        _condVar.notify_one();
        _clientThread.value().join();
        lock.lock();
        _clientThread = std::nullopt;
    }
    else if (!omitExtraLogs)
    {
        _logger.log("Client thread not running");
    }

    if ((::close(_fdSocket) == -1) && (errno != EBADF))
    {
        _logger.log("Socket with descriptor " + std::to_string(_fdSocket)
            + " closed with error: " + std::string{ strerror(errno) },
            LoggingLevel::WARNING);
    }
    else
    {
        _logger.log("Successfully closed socket with descriptor: "
            + std::to_string(_fdSocket));

        _fdSocket = -1;
        _fdMonitor = { -1, 0, 0 };
    }

    if (_clientThread.has_value())
    {
        _clientThread.value().join();
    }
    _shutdownRequested = false;

    _logger.log("Shutdown socket client", LoggingLevel::INFO);
}

bool SocketClient::isOperational() const
{
    std::lock_guard<std::mutex> lock{ _mutex };
    return _operational;
}

void SocketClient::enableServerWait(const bool enabled)
{
    std::lock_guard<std::mutex> lock{ _mutex };
    _serverWait = enabled;
}

bool SocketClient::serverWaitEnabled() const
{
    std::lock_guard<std::mutex> lock{ _mutex };
    return _serverWait;
}

void SocketClient::close()
{
    shutdown(false);
}

#include <iostream>
#include <iomanip>
void SocketClient::clientThreadFunc()
{
    static std::ofstream dbgOut{ "dbgOut.csv" };
    dbgOut << std::setprecision(17);

    const auto waitDuration = std::chrono::milliseconds(100);
    const auto waitPredicate = [this]()
    {
        if (_shutdownRequested)
        {
            return true;
        }

        auto retVal = poll(&_fdMonitor, 1, 0);
        if (retVal > 0)
        {
            if (_fdMonitor.revents & POLLIN)
            {
                _fdMonitor.revents = 0;
                return true;
            }
        }

        return false;
    };
    bool shutdownAck = false;

    _logger.log("Client thread initialized, working...");

    while (true)
    {
        std::unique_lock<std::mutex> lock{ _mutex };
        // _logger.log("Waiting for notification...");

        while (_condVar.wait_for(lock, waitDuration, waitPredicate) == false);

        // _logger.log("Notified, resumed activity");

        if (_shutdownRequested && !shutdownAck)
        {
            shutdownAck = true;
            if (!_serverWait)
            {
                _logger.log("Shutdown request acknowledged");
                lock.unlock();
                break;
            }
            else
            {
                _logger.log("Shutdown request acknowledged, thread will"
                    " terminate when server closes connection");
            }
        }

        /*
        double arrbuf[3];

    const int requiredTotalBytesReceived = 24;
    int totalBytesReceived = 0;

    while ((bytesReceived = recv(client_sock_fd, arrbuf,
        requiredTotalBytesReceived - totalBytesReceived, 0)) > 0)
    {
        // tmpOut << bytesReceived << "\n";
        totalBytesReceived += bytesReceived;
        if (totalBytesReceived == requiredTotalBytesReceived)
        {
            entries.push(TransmOut{ arrbuf[0], arrbuf[1], arrbuf[2] });
            totalBytesReceived = 0;
        }
        // queueCV.notify_one();
    }*/

        static double buf[3];
        const auto requiredTotalBytes = sizeof(buf);
        ssize_t retVal = 0;
        static auto totalRecvBytes = retVal;
        while (retVal = recv(_fdSocket, buf + (totalRecvBytes / sizeof(double)),
            requiredTotalBytes - totalRecvBytes, MSG_DONTWAIT))
        {
            if (retVal == 0)
            {
                break;
            }
            else if (retVal > 0)
            {
                totalRecvBytes += retVal;
                if (totalRecvBytes == requiredTotalBytes)
                {
                    dbgOut << buf[0] << "," << buf[1] << "," << buf[2] << "\n";
                    totalRecvBytes = 0;
                }
            }
            else if (retVal == -1)
            {
                if ((errno == EAGAIN) || (errno == EWOULDBLOCK))
                {
                    _logger.log("Receive operation would block at "
                        + std::to_string(totalRecvBytes) + " bytes");
                    break;
                }
                else
                {
                    const std::system_error error{ errno, std::system_category(),
                        "Could not receive message" };
                    _logger.log(error.what(), LoggingLevel::ERROR);
                    throw error;
                }
            }
        }

        if (retVal == 0)
        {
            _logger.log("Server closed the connection, client no longer"
                " operational", LoggingLevel::INFO);
                _operational = false;
            lock.unlock();
            break;
        }
        // else
        // {
        //     // _dataQueue.push_back(DataTransferObject{ buf[0], buf[1], buf[2] });
        //     dbgOut << buf[0] << "," << buf[1] << "," << buf[2] << '\n';
        // }

        lock.unlock();
    }

    _logger.log("Client thread terminated");
}

const std::string SocketClient::defaultIpAddress = "127.0.0.1";
