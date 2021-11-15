/**
 * @file TraceContext.cpp
 * @author Vlad Zahiu (vladzahiu28@gmail.com)
 * @brief Implements the TraceContext class.
 * @version 0.1
 * @date 2021-11-15
 * 
 * @copyright Copyright (c) 2021
 */

#include "TraceContext.h"

TraceContext::TraceContext(const std::optional<std::string>& contextId,
    const SourceLocation& location)
    : _contextId{ contextId }, _location{ location } {}

std::optional<std::string> TraceContext::getContextId() const noexcept
{
    return _contextId;
}

void TraceContext::setContextId(const std::optional<std::string>& contextId)
    noexcept
{
    _contextId = contextId;
}

SourceLocation TraceContext::getSourceLocation() const noexcept
{
    return _location;
}

void TraceContext::setSourceLocation(const SourceLocation& location) noexcept
{
    _location = location;
}