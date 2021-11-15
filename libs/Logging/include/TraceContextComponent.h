/**
 * @file TraceContextComponent.h
 * @author Vlad Zahiu (vladzahiu28@gmail.com)
 * @brief Defines the TraceContextComponent class.
 * @version 0.2
 * @date 2021-11-15
 * 
 * @copyright Copyright (c) 2021
 */

#ifndef TRACE_CONTEXT_H
#define TRACE_CONTEXT_H

#include "ITraceComponent.h"
#include "SourceLocation.h"

#include <optional>

class TraceContextComponent : virtual public ITraceComponent
{
public:
    TraceContextComponent(const std::optional<std::string>& contextId = std::nullopt,
        const SourceLocation& location = {});

    std::optional<std::string> getContextId() const noexcept;
    void setContextId(const std::optional<std::string>& contextId) noexcept;
    SourceLocation getSourceLocation() const noexcept;
    void setSourceLocation(const SourceLocation& location) noexcept;

    explicit operator std::string() const override;

private:
    std::optional<std::string> _contextId;
    SourceLocation _location;
};

#endif