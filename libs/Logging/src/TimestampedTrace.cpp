/**
 * @file TimestampedTrace.cpp
 * @author Vlad Zahiu (vladzahiu28@gmail.com)
 * @brief Implements the TimestampedTrace class.
 * @version 0.1
 * @date 2021-11-14
 * 
 * @copyright Copyright (c) 2021
 */

#include "TimestampedTrace.h"

TimestampedTrace::TimestampedTrace(const std::string& msg,
    const Timestamp_t& timestamp)
    : BasicTrace(msg),
    _timestamp{ timestamp } {}

TimestampedTrace::Timestamp_t TimestampedTrace::getTimestamp() const noexcept
{
    return _timestamp;
}

void TimestampedTrace::setTimestamp(const Timestamp_t& timestamp) noexcept
{
    _timestamp = timestamp;
}

TimestampedTrace::operator std::string() const
{
    return ("[" + strTimestamp(_timestamp) + "] " + getMessage());
}

std::string TimestampedTrace::strTimestamp(const Timestamp_t& timestamp) const
{
    constexpr std::size_t microsPrecision = 5;
    constexpr std::size_t microsPerSec = 1000000;
    constexpr std::size_t bufSize = 1024;
    constexpr const char* const timeFormat = "%F %T";
    char buf[bufSize];
    const std::time_t timeT = std::chrono::system_clock::to_time_t(timestamp);
    const tm* tmT = std::localtime(&timeT);

    if (std::strftime(buf, bufSize, timeFormat, tmT) == 0)
    {
        throw std::system_error(errno, std::system_category(),
            "Could not format timestamp");
    }

    std::string strTimestamp{ buf };
    const auto timestampInMicros
        = std::chrono::time_point_cast<std::chrono::microseconds>(timestamp);
    const auto micros = timestampInMicros.time_since_epoch().count();
    const auto microsRem = (micros % microsPerSec);
    std::string strMicrosRem = std::to_string(microsRem);

    if (strMicrosRem.length() > microsPrecision)
    {
        strMicrosRem = strMicrosRem.substr(0, microsPrecision);
    }
    else
    {
        const auto precisionDif = microsPrecision - strMicrosRem.length();
        strMicrosRem = std::string(precisionDif, '0') + strMicrosRem;
    }

    strTimestamp += "." + strMicrosRem;

    return strTimestamp;
}