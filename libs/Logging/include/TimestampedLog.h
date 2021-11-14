/**
 * @file TimestampedLog.h
 * @author Vlad Zahiu (vladzahiu28@gmail.com)
 * @brief Defines the TimestampedLog class.
 * @version 0.1
 * @date 2021-11-14
 * 
 * @copyright Copyright (c) 2021
 */
#ifndef TIMESTAMPED_LOG_H
#define TIMESTAMPED_LOG_h

#include "BasicLog.h"

#include <chrono>

class TimestampedLog : public BasicLog
{
public:
    using Timestamp_t = std::chrono::system_clock::time_point;

    TimestampedLog(const std::string& msg,
        const Timestamp_t& timestamp = std::chrono::system_clock::now());

    Timestamp_t getTimestamp() const noexcept;
    void setTimestamp(const Timestamp_t& timestamp) noexcept;

    explicit operator std::string() const override;

protected:
    std::string strTimestamp(const Timestamp_t& timestamp) const;

private:
    Timestamp_t _timestamp;
};

#endif