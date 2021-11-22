#ifndef TRACE_CONTEXT_H
#define TRACE_CONTEXT_H

#include "SourceLocation.h"
#include "ProcessContext.h"

#include <optional>

class TraceContext
{
public:
    TraceContext(const std::optional<std::string>& contextId = std::nullopt,
        const ProcessContext& processContext = {},
        const SourceLocation& location = {});

    std::optional<std::string> getContextId() const noexcept;
    SourceLocation getSourceLocation() const noexcept;
    ProcessContext getProcessContext() const noexcept;

    void setContextId(const std::optional<std::string>& contextId) noexcept;
    void setSourceLocation(const SourceLocation& location) noexcept;
    void setProcessContext(const ProcessContext& processContext) noexcept;

private:
    std::optional<std::string> _contextId;
    SourceLocation _location;
    ProcessContext _procContext;
};

#endif