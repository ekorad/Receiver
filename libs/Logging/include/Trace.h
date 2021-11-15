/**
 * @file Trace.h
 * @author Vlad Zahiu (vladzahiu28@gmail.com)
 * @brief Defines the Trace class.
 * @version 0.1
 * @date 2021-11-15
 * 
 * @copyright Copyright (c) 2021
 */

#ifndef TRACE_H
#define TRACE_H

#include "TraceMessageComponent.h"
#include "TraceTimestampComponent.h"
#include "TraceLevelComponent.h"
#include "TraceContextComponent.h"

class Trace : public TraceMessageComponent, public TraceTimestampComponent,
    public TraceLevelComponent, public TraceContextComponent
{
public:
    Trace(const std::string& msg = "",
        const std::optional<std::string>& contextId = std::nullopt,
        const LoggingLevel level = LoggingLevel::INFO,
        const Timestamp_t& timestamp = std::chrono::system_clock::now(),
        const SourceLocation& location = {});

    explicit operator std::string() const override;
};

#endif