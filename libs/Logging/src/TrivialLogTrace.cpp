#include "TrivialLogTrace.h"

TrivialLogTrace::TrivialLogTrace(const std::string& message)
	: _message{ message } {}

std::string TrivialLogTrace::getMessage() const noexcept
{
	return _message;
}

void TrivialLogTrace::setMessage(const std::string& message) noexcept
{
	_message = message;
}

TrivialLogTrace::operator std::string() const
{
	return getMessage();
}

std::ostream& operator<<(std::ostream& outStream, const TrivialLogTrace& trace)
{
	outStream << static_cast<std::string>(trace);
	return outStream;
}