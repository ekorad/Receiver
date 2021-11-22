#include "Logger.h"

Logger::Logger(const std::string& contextId)
    : _contextId{ contextId }
{
    if (!_service.isOperational())
    {
        _service.start();
    }

    std::unique_lock<std::mutex> lock{ staticMutex };
    registeredLoggers.push_back(this);
    lock.unlock();

    log("Registered logger");
}

Logger::~Logger()
{
    std::unique_lock<std::mutex> lock{ staticMutex };
    registeredLoggers.erase(std::remove(registeredLoggers.begin(),
        registeredLoggers.end(), this));
    lock.unlock();

    log("Unregistered logger");
}

void Logger::setDefaultMinimumLoggingLevel(const LoggingLevel level)
{
    if (!isValidLoggingLevel(level))
    {
        throw std::runtime_error("Invalid logging level");
    }
    defaultMinLogLevel.store(static_cast<int>(level));
}

LoggingLevel Logger::getDefaultMinimumLoggingLevel()
{
    return static_cast<LoggingLevel>(defaultMinLogLevel.load());
}

void Logger::pause()
{
    _paused.store(true);
}

void Logger::resume()
{
    _paused.store(true);
}

bool Logger::isPaused() const
{
    return _paused.load();
}

void Logger::setMinimumLoggingLevel(const LoggingLevel level)
{
    if (!isValidLoggingLevel(level))
    {
        throw std::runtime_error("Invalid logging level");
    }
    _minLogLevel.store(static_cast<int>(level));
}

LoggingLevel Logger::getMinimumLoggingLevel() const
{
    return static_cast<LoggingLevel>(_minLogLevel.load());
}

void Logger::log(const std::string& traceMessage, const LoggingLevel level,
    const SourceLocation& location)
{
    if (static_cast<int>(level) >= _minLogLevel)
    {
        LogTrace trace{ traceMessage, _contextId, level, _logCount.load(), location };
        _service.pushTrace(trace);
        _logCount++;
    }
}

std::atomic_int Logger::defaultMinLogLevel{ static_cast<int>(LoggingLevel::DEBUG) };
std::vector<Logger*> Logger::registeredLoggers;
std::mutex Logger::staticMutex;