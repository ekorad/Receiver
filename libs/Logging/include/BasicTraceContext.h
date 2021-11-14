/**
 * @file BasicTraceContext.h
 * @author Vlad Zahiu (vladzahiu28@gmail.com)
 * @brief Defines the BasicTraceContext class.
 * @version 0.1
 * @date 2021-11-14
 *
 * @copyright Copyright (c) 2021
 */

#ifndef BASIC_TRACE_CONTEXT_H
#define BASIC_TRACE_CONTEXT_H

#ifndef BASIC_TRACE_CONTEXT_PARAMS
#define BASIC_TRACE_CONTEXT_PARAMS  __FUNCTION__, std::nullopt
#define GEN_BASIC_TRACE_CTXT()      BasicTraceContext{ \
    BASIC_TRACE_CONTEXT_PARAMS }
#define GBTC()                      GEN_BASIC_TRACE_CTXT()
#endif

#include <string>
#include <optional>

class BasicTraceContext
{
public:
    BasicTraceContext(const std::string& funcName,
        const std::optional<std::string> callContext = std::nullopt);

    static std::string extractFileName(const std::string path) noexcept;

    std::string getFunctionName() const noexcept;
    void setFunctionName(const std::string& funcName) noexcept;
    std::optional<std::string> getCallContext() const noexcept;
    void setCallContext(const std::string& callContext) noexcept;

private:
    std::string _func;
    std::optional<std::string> _callContext;
};

#endif