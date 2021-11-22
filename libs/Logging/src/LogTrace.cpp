#include "LogTrace.h"

LogTrace::LogTrace(const std::string& message, const std::optional<std::string>& contextId,
	const LoggingLevel level, const std::optional<std::size_t> traceIndex,
	const SourceLocation& sourceLocation, const ProcessContext& processContext,
	const TimestampContainer::Timestamp_t& timestamp)
	: LightweightLogTrace{ message, level, timestamp },
	TraceContext{ contextId, processContext, sourceLocation },
	_currentTraceIndex{ traceIndex } {}

std::size_t LogTrace::getCurrentGlobalTraceIndex()
{
	return currentGlobalTraceIndex.load();
}

std::optional<std::size_t> LogTrace::getCurrentTraceIndex() const
{
	return _currentTraceIndex;
}

void LogTrace::setCurrentTraceIndex(const std::size_t traceIndex)
{
	_currentTraceIndex = traceIndex;
}

LogTrace::operator std::string() const
{
	currentGlobalTraceIndex++;
	return ("[" + std::to_string(currentGlobalTraceIndex.load()) + "]["
		+ timestampToTraceString(getTimestamp()) + "]["
		+ (getCurrentTraceIndex().has_value() ? std::to_string(getCurrentTraceIndex().value()) + "][" : "")
		+ std::to_string(getProcessContext().getProcessId()) + "-"
		+ std::to_string(getProcessContext().getThreadId()) + "]["
		+ loggingLevelToString(getLevel()) + "]["
		+ (getContextId().has_value() ? (getContextId().value() + "][") : "")
		+ getSourceLocation().getFunctionName() + "] "
		+ TrivialLogTrace::operator std::string());
}

std::atomic_uint64_t LogTrace::currentGlobalTraceIndex;