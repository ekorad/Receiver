/**
 * @file TimestampedTrace.h
 * @author Vlad Zahiu (vladzahiu28@gmail.com)
 * @brief Defines the TimestampedTrace class.
 * @version 0.1
 * @date 2021-11-14
 * 
 * @copyright Copyright (c) 2021
 */
#ifndef TIMESTAMPED_TRACE_H
#define TIMESTAMPED_TRACE_H

#include "BasicTrace.h"

#include <chrono>

class TimestampedTrace : public BasicTrace
{
public:
    using Timestamp_t = std::chrono::system_clock::time_point;

    TimestampedTrace(const std::string& msg,
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