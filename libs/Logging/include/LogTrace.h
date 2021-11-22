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
		const std::optional<std::size_t> count = std::nullopt,
		const SourceLocation& sourceLocation = {},
		const ProcessContext& processContext = {},
		const TimestampContainer::Timestamp_t& timestamp = TimestampContainer::getTimestampNow());

	static std::size_t getGlobalCount();

	std::optional<std::size_t> getCount() const;
	void setCount(const std::size_t count);

	explicit operator std::string() const override;

private:
	static std::atomic_uint64_t globalCount;

	std::optional<std::size_t> _count;
};

#endif