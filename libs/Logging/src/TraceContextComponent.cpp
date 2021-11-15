/**
 * @file TraceContextComponent.cpp
 * @author Vlad Zahiu (vladzahiu28@gmail.com)
 * @brief Implements the TraceContextComponent class.
 * @version 0.1
 * @date 2021-11-15
 * 
 * @copyright Copyright (c) 2021
 */

#include "TraceContextComponent.h"

TraceContextComponent::TraceContextComponent(const std::optional<std::string>& contextId,
    const SourceLocation& location)
    : _contextId{ contextId }, _location{ location } {}

std::optional<std::string> TraceContextComponent::getContextId() const noexcept
{
    return _contextId;
}

void TraceContextComponent::setContextId(const std::optional<std::string>& contextId)
    noexcept
{
    _contextId = contextId;
}

SourceLocation TraceContextComponent::getSourceLocation() const noexcept
{
    return _location;
}

void TraceContextComponent::setSourceLocation(const SourceLocation& location) noexcept
{
    _location = location;
}

TraceContextComponent::operator std::string() const
{
    std::string retVal;

    if (_contextId.has_value())
    {
        retVal += "[" + _contextId.value() + "]";
    }
    retVal += "[" + _location.getFunctionName() + "]";

    return retVal;
}