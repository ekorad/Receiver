#include "TimestampContainer.h"

#include <system_error>

TimestampContainer::TimestampContainer(const Timestamp_t& timestamp)
    : _timestamp{ timestamp } {}

TimestampContainer::Timestamp_t TimestampContainer::getTimestamp()
const noexcept
{
    return _timestamp;
}

void TimestampContainer::setTimestamp(const Timestamp_t& timestamp)
noexcept
{
    _timestamp = timestamp;
}

std::string TimestampContainer::timestampToTraceString(
    const Timestamp_t& timestamp)
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