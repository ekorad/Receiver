/**
 * @file Trace.cpp
 * @author Vlad Zahiu (vladzahiu28@gmail.com)
 * @brief Implements the Trace class.
 * @version 0.1
 * @date 2021-11-15
 * 
 * @copyright Copyright (c) 2021
 */

#include "Trace.h"

Trace::Trace(const std::string& msg,
    const std::optional<std::string>& contextId,
    const LoggingLevel level, const Timestamp_t& timestamp,
    const SourceLocation& location)
    : TraceMessageComponent{ msg }, TraceTimestampComponent{ timestamp },
    TraceLevelComponent{ level }, TraceContextComponent{ contextId, location }
    {}

Trace::operator std::string() const
{
    return (TraceTimestampComponent::operator std::string()
        + TraceLevelComponent::operator std::string()
        + TraceContextComponent::operator std::string()
        + " " + TraceMessageComponent::operator std::string());
}