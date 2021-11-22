#include "LightweightLogTrace.h"

LightweightLogTrace::LightweightLogTrace(const std::string& message,
	const LoggingLevel level, TimestampContainer::Timestamp_t timestamp)
	: TrivialLogTrace{ message }, LoggingLevelContainer{ level },
	TimestampContainer{ timestamp } {}

LightweightLogTrace::operator std::string() const
{
	return ("[" + timestampToTraceString(getTimestamp()) + "]["
		+ loggingLevelToString(getLevel()) + "] "
		+ TrivialLogTrace::operator std::string());
}
