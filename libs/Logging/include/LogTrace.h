#ifndef LOG_TRACE_H
#define LOG_TRACE_H

#include "LightweightLogTrace.h"
#include "TraceContext.h"

#include <atomic>

class LogTrace : public LightweightLogTrace, public TraceContext
{
public:
	LogTrace(const std::string& message = "",
		const std::optional<std::string>& contextId = std::nullopt,
		const LoggingLevel level = LoggingLevel::DEBUG,
		const std::optional<std::size_t> traceIndex = std::nullopt,
		const SourceLocation& sourceLocation = {},
		const ProcessContext& processContext = {},
		const TimestampContainer::Timestamp_t& timestamp = TimestampContainer::getTimestampNow());

	static std::size_t getCurrentGlobalTraceIndex();

	std::optional<std::size_t> getCurrentTraceIndex() const;
	void setCurrentTraceIndex(const std::size_t traceIndex);

	explicit operator std::string() const override;

private:
	static std::atomic_uint64_t currentGlobalTraceIndex;

	std::optional<std::size_t> _currentTraceIndex;
};

#endif