#ifndef LOGGING_LEVEL_CONTAINER_H
#define LOGGING_LEVEL_CONTAINER_H

#include "LoggingLevel.h"

class LoggingLevelContainer
{
public:
    LoggingLevelContainer(const LoggingLevel level = LoggingLevel::INFO);

    LoggingLevel getLevel() const noexcept;
    void setLevel(const LoggingLevel level);

private:
    LoggingLevel _level;
};

#endif