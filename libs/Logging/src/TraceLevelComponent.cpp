/**
 * @file TraceLevelComponent.cpp
 * @author Vlad Zahiu (vladzahiu28@gmail.com)
 * @brief Implements the TraceLevelComponent class.
 * @version 0.1
 * @date 2021-11-15
 * 
 * @copyright Copyright (c) 2021
 */

#include "TraceLevelComponent.h"

TraceLevelComponent::TraceLevelComponent(const LoggingLevel& level)
{
    if (!isValidLoggingLevel(level))
    {
        throw std::runtime_error{ "Invalid logging level" };
    }
    _level = level;
}

LoggingLevel TraceLevelComponent::getLevel() const noexcept
{
    return _level;
}

void TraceLevelComponent::setLevel(const LoggingLevel level)
{
    if (!isValidLoggingLevel(level))
    {
        throw std::runtime_error{ "Invalid logging level" };
    }
    _level = level;
}

TraceLevelComponent::operator std::string() const
{
    return ("[" + loggingLevelToString(_level) + "]");
}