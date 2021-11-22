#include "SocketClient.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

SocketClient::SocketClient(const std::string& ipAddress, const unsigned port)
{
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

    _logger.log("Initialized socket client");
}

SocketClient::~SocketClient()
{
    shutdown();

    _logger.log("Destroyed socket client", LoggingLevel::INFO);
}

void SocketClient::shutdown()
{
    if (_fdSocket != -1)
    {
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
        }
        _logger.log("Shutdown socket client", LoggingLevel::INFO);
    }
    else
    {
        _logger.log("Socket descriptor already closed", LoggingLevel::INFO);
    }
}

const std::string SocketClient::defaultIpAddress = "127.0.0.1";
