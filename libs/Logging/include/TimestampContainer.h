#ifndef I_TIMESTAMPED_H
#define I_TIMESTAMPED_H

#include <chrono>
#include <string>

class TimestampContainer
{
public:
	using Timestamp_t = std::chrono::system_clock::time_point;

	TimestampContainer(const Timestamp_t& timestamp = getTimestampNow());

	static std::string timestampToTraceString(const Timestamp_t& timestamp);
	static inline Timestamp_t getTimestampNow() noexcept;

	Timestamp_t getTimestamp() const noexcept;
	void setTimestamp(const Timestamp_t& timestamp) noexcept;

private:
	Timestamp_t _timestamp;
};

inline TimestampContainer::Timestamp_t TimestampContainer::getTimestampNow() noexcept
{
	return std::chrono::system_clock::now();
}

#endif