#ifndef PROCESS_CONTEXT_H
#define PROCESS_CONTEXT_H

class ProcessContext
{
public:
    ProcessContext(const unsigned long processId = getCurrentProcessId(),
        const unsigned long threadId = getCurrentThreadId());

    static unsigned long getCurrentProcessId() noexcept;
    static unsigned long getCurrentThreadId() noexcept;

    unsigned long getProcessId() const noexcept;
    unsigned long getThreadId() const noexcept;

    void setProcessId(const unsigned long processId) noexcept;
    void setThreadId(const unsigned long threadId) noexcept;

private:
    unsigned long _pid;
    unsigned long _tid;
};

#endif