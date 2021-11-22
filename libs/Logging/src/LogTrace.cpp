#include "LogTrace.h"

LogTrace::LogTrace(const std::string& message, const std::optional<std::string>& contextId,
	const LoggingLevel level, const std::optional<std::size_t> count,
	const SourceLocation& sourceLocation, const ProcessContext& processContext,
	const TimestampContainer::Timestamp_t& timestamp)
	: LightweightLogTrace{ message, level, timestamp },
	TraceContext{ contextId, processContext, sourceLocation },
	_count{ count } {}

std::size_t LogTrace::getGlobalCount()
{
	return globalCount.load();
}

std::optional<std::size_t> LogTrace::getCount() const
{
	return _count;
}

void LogTrace::setCount(const std::size_t count)
{
	_count = count;
}

LogTrace::operator std::string() const
{
	globalCount++;
	return ("[" + std::to_string(globalCount.load()) + "]["
		+ timestampToTraceString(getTimestamp()) + "]["
		+ (getCount().has_value() ? std::to_string(getCount().value()) + "][" : "")
		+ std::to_string(getProcessContext().getProcessId()) + "-"
		+ std::to_string(getProcessContext().getThreadId()) + "]["
		+ loggingLevelToString(getLevel()) + "]["
		+ (getContextId().has_value() ? (getContextId().value() + "][") : "")
		+ getSourceLocation().getFunctionName() + "] "
		+ TrivialLogTrace::operator std::string());
}

std::atomic_uint64_t LogTrace::globalCount;