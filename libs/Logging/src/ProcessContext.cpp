#include "ProcessContext.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

ProcessContext::ProcessContext(const unsigned long processId,
    const unsigned long threadId)
    : _pid{ processId }, _tid{ threadId } {}

unsigned long ProcessContext::getCurrentProcessId() noexcept
{
#ifdef _WIN32
    return GetCurrentProcessId();
#else
    return getpid();
#endif
}

unsigned long ProcessContext::getCurrentThreadId() noexcept
{
#ifdef _WIN32
    return GetCurrentThreadId();
#else
    return gettid();
#endif
}

void ProcessContext::setProcessId(const unsigned long processId) noexcept
{
    _pid = processId;
}

unsigned long ProcessContext::getProcessId() const noexcept
{
    return _pid;
}

void ProcessContext::setThreadId(const unsigned long threadId) noexcept
{
    _tid = threadId;
}

unsigned long ProcessContext::getThreadId() const noexcept
{
    return _tid;
}