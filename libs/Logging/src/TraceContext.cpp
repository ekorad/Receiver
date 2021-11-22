#include "TraceContext.h"

TraceContext::TraceContext(const std::optional<std::string>& contextId,
	const ProcessContext& processContext,
	const SourceLocation& location)
	: _contextId{ contextId }, _procContext{ processContext }, _location{ location } {}

std::optional<std::string> TraceContext::getContextId() const noexcept
{
	return _contextId;
}

SourceLocation TraceContext::getSourceLocation() const noexcept
{
	return _location;
}

ProcessContext TraceContext::getProcessContext() const noexcept
{
	return _procContext;
}

void TraceContext::setContextId(const std::optional<std::string>& contextId) noexcept
{
	_contextId = contextId;
}

void TraceContext::setSourceLocation(const SourceLocation& location) noexcept
{
	_location = location;
}

void TraceContext::setProcessContext(const ProcessContext& processContext) noexcept
{
	_procContext = processContext;
}