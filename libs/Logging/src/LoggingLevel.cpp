/**
 * @file LoggingLevel.cpp
 * @author Vlad Zahiu (vladzahiu28@gmail.com)
 * @brief Implements the utility functionality for the LoggingLevel enum.
 * @version 0.1
 * @date 2021-11-14
 * 
 * @copyright Copyright (c) 2021
 */

#include "LoggingLevel.h"

#include <stdexcept>

bool isValidLoggingLevel(const LoggingLevel level) noexcept
{
    return (level >= LoggingLevel::DEBUG)
        && (level <= LoggingLevel::FATAL);
}

std::string loggingLevelToString(const LoggingLevel level)
{
    if (!isValidLoggingLevel(level))
    {
        throw std::runtime_error("Invalid logging level");
    }

    switch (level)
    {
        case LoggingLevel::DEBUG:
            return "DEBUG";
        case LoggingLevel::INFO:
            return "INFO";
        case LoggingLevel::WARNING:
            return "WARNING";
        case LoggingLevel::ERROR:
            return "ERROR";
        case LoggingLevel::FATAL:
            return "FATAL";
        default:
            throw std::runtime_error("Invalid logging level");
    }
}