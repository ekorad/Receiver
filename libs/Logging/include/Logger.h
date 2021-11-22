#ifndef LOGGER_H
#define LOGGER_H

#include "LoggerService.h"
#include "LogTrace.h"

#include <vector>

class Logger
{
public:
    Logger(const std::string& contextId);
    virtual ~Logger();

    static void setDefaultMinimumLoggingLevel(const LoggingLevel level);
    static LoggingLevel getDefaultMinimumLoggingLevel();

    void pause();
    void resume();

    bool isPaused() const;

    void setMinimumLoggingLevel(const LoggingLevel level);
    LoggingLevel getMinimumLoggingLevel() const;

    void log(const std::string& traceMessage,
        const LoggingLevel level = LoggingLevel::DEBUG,
        const SourceLocation& location = {});

private:
    static std::atomic_int defaultMinLogLevel;
    static std::vector<Logger*> registeredLoggers;
    static std::mutex staticMutex;

    LoggerService& _service = LoggerService::getInstance();
    const std::string _contextId;

    std::atomic_bool _paused = false;
    std::atomic_int _minLogLevel = defaultMinLogLevel.load();
    std::atomic_uint64_t _currentTraceIndex = 0;
};

#endif