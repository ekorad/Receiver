#ifndef TRIVIAL_LOG_TRACE_H
#define TRIVIAL_LOG_TRACE_H

#include <string>
#include <ostream>

class TrivialLogTrace
{
public:
    TrivialLogTrace(const std::string& message = "");

    std::string getMessage() const noexcept;
    void setMessage(const std::string& message) noexcept;

    virtual explicit operator std::string() const;

    friend std::ostream& operator<<(std::ostream& outStream, const TrivialLogTrace& trace);

private:
    std::string _message;
};

#endif