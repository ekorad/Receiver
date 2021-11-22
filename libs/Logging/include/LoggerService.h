#ifndef LOGGER_SERVICE_H
#define LOGGER_SERVICE_H

/* ************************************************************************** */
/* ******************************** INCLUDES ******************************** */
/* ************************************************************************** */

#include "TrivialLogTrace.h"

#include <vector>
#include <fstream>
#include <mutex>
#include <memory>
#include <optional>
#include <condition_variable>
#include <thread>

/* ************************************************************************** */
/* ********************************* CLASSES ******************************** */
/* ************************************************************************** */

class LoggerService
{
public:
    enum class ShutdownRequest
    {
        NONE,
        GRACEFUL,
        FORCEFUL
    };

    ~LoggerService();

    static LoggerService& getInstance();

    void start();
    void pause();
    void resume();
    void stop(const bool flush = true) noexcept;
    template <typename LogTraceType>
    void pushTrace(const LogTraceType& trace);

    bool isOperational() const noexcept;
    bool isPaused() const noexcept;

    void setLogFileName(const std::string& fileName);
    std::string getLogFileName() const noexcept;
    void enableFileAppend(const bool enabled = true);
    bool fileAppendEnabled() const noexcept;

private:
    const static std::string defaultFileName;

    LoggerService() {}

    void loggingThreadFunc();

    std::vector<std::unique_ptr<TrivialLogTrace>> _traceQueue;
    std::string _fileName = defaultFileName;
    bool _fileAppend = false;
    std::ofstream _outStream;

    std::optional<std::thread> _loggingThread;
    mutable std::mutex _mutex;
    std::condition_variable _condVar;
    bool _operational = false;
    bool _pauseRequested = false;
    ShutdownRequest _shutdownRequested = ShutdownRequest::NONE;
};

template <typename LogTraceType>
void LoggerService::pushTrace(const LogTraceType& trace)
{
    std::unique_lock<std::mutex> stateLock{ _mutex };

    if (!_operational)
    {
        throw std::runtime_error("Service is not operational");
    }

    if (_pauseRequested)
    {
        throw std::runtime_error("Can not push new trace when service is paused");
    }

    bool firstTrace = _traceQueue.empty();

    _traceQueue.push_back(std::make_unique<LogTraceType>( trace ));

    if (firstTrace)
    {
        stateLock.unlock();
        _condVar.notify_one();
    }
}

#endif