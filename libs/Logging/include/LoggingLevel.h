/**
 * @file LoggingLevel.h
 * @author Vlad Zahiu (vladzahiu28@gmail.com)
 * @brief Defines the LoggingLevel enum and any associated utility functionality.
 * @version 0.1
 * @date 2021-11-14
 * 
 * @copyright Copyright (c) 2021
 */

#ifndef LOGGING_LEVEL_H
#define LOGGING_LEVEL_H

#include <string>

enum class LoggingLevel
{
    DEBUG = 0,
    INFO,
    WARNING,
    ERROR,
    FATAL
};

bool isValidLoggingLevel(const LoggingLevel level) noexcept;

std::string loggingLevelToString(const LoggingLevel level);

#endif