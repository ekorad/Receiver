#include "SocketClient.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
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

    _logger.log("Socket client operational", LoggingLevel::INFO);
}

SocketClient::~SocketClient()
{
    shutdown(false);

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
        _shutdownRequested = true;
        lock.unlock();
        _condVar.notify_one();
        _logger.log("Requesting client thread shutdown...");
        _clientThread.value().join();
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
    }

    _clientThread = std::nullopt;
    _shutdownRequested = false;

    _logger.log("Shutdown socket client", LoggingLevel::INFO);
}

bool SocketClient::isOperational() const
{
    std::lock_guard<std::mutex> lock{ _mutex };
    return _operational;
}

void SocketClient::close()
{
    shutdown(false);
}

void SocketClient::clientThreadFunc()
{
    const auto waitDuration = std::chrono::milliseconds(100);
    const auto waitPredicate = [this]()
    {
        if (this->_shutdownRequested)
        {
            return true;
        }

        return false;
    };

    _logger.log("Client thread initialized");

    while (true)
    {
        std::unique_lock<std::mutex> lock{ _mutex };
        _logger.log("Waiting for notification...");

        while (_condVar.wait_for(lock, waitDuration, waitPredicate) == false);

        _logger.log("Notified, resumed activity");

        if (_shutdownRequested)
        {
            _logger.log("Shutdown request acknowledged");
            lock.unlock();
            break;
        }
        else
        {
            lock.unlock();
        }

    }

    _logger.log("Client thread terminated");
}

const std::string SocketClient::defaultIpAddress = "127.0.0.1";
