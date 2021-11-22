#ifndef LIGHTWEIGHT_LOG_TRACE_H
#define LIGHTWEIGHT_LOG_TRACE_H

#include "TrivialLogTrace.h"
#include "TimestampContainer.h"
#include "LoggingLevelContainer.h"

class LightweightLogTrace : public TrivialLogTrace, public TimestampContainer,
	public LoggingLevelContainer
{
public:
	LightweightLogTrace(const std::string& message = "",
		const LoggingLevel level = LoggingLevel::DEBUG,
		TimestampContainer::Timestamp_t timestamp = TimestampContainer::getTimestampNow());

	explicit operator std::string() const override;
};

#endif