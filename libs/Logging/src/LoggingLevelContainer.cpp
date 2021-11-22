#include "LoggingLevelContainer.h"

#include <stdexcept>

LoggingLevelContainer::LoggingLevelContainer(const LoggingLevel level)
{
    if (!isValidLoggingLevel(level))
    {
        throw std::runtime_error{ "Invalid logging level" };
    }
    _level = level;
}

LoggingLevel LoggingLevelContainer::getLevel() const noexcept
{
    return _level;
}

void LoggingLevelContainer::setLevel(const LoggingLevel level)
{
    if (!isValidLoggingLevel(level))
    {
        throw std::runtime_error{ "Invalid logging level" };
    }
    _level = level;
}