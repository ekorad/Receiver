/**
 * @file TraceTimestampComponent.h
 * @author Vlad Zahiu (vladzahiu28@gmail.com)
 * @brief Defines the TraceTimestampComponent class.
 * @version 0.1
 * @date 2021-11-14
 * 
 * @copyright Copyright (c) 2021
 */
#ifndef TRACE_TIMESTAMP_H
#define TRACE_TIMESTAMP_H

#include "ITraceComponent.h"

#include <chrono>

class TraceTimestampComponent : virtual public ITraceComponent
{
public:
    using Timestamp_t = std::chrono::system_clock::time_point;

    TraceTimestampComponent(const Timestamp_t& timestamp
        = std::chrono::system_clock::now());

    static std::string timestampTraceString(const Timestamp_t& timestamp);

    Timestamp_t getTimestamp() const noexcept;
    void setTimestamp(const Timestamp_t& timestamp) noexcept;

    explicit operator std::string() const override;

private:
    Timestamp_t _timestamp;
};

#endif