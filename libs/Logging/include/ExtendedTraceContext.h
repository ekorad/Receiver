/**
 * @file ExtendedTraceContext.h
 * @author Vlad Zahiu (vladzahiu28@gmail.com)
 * @brief Defines the ExtendedTraceContext class.
 * @version 0.1
 * @date 2021-11-14
 * 
 * @copyright Copyright (c) 2021
 */

#ifndef EXTENDED_TRACE_CONTEXT_H
#define EXTENDED_TRACE_CONTEXT_H

#ifndef EXTENDED_TRACE_CONTEXT_PARAMS
#define EXTENDED_TRACE_CONTEXT_PARAMS   __FUNCTION__, std::nullopt, \
    ExtendedTraceContext::extractFileName(__FILE__), __LINE__
#define GEN_EXT_TRACE_CTXT()            ExtendedTraceContext{ \
    EXTENDED_TRACE_CONTEXT_PARAMS }
#define GETC()                          GEN_EXT_TRACE_CTXT()
#endif

#include "BasicTraceContext.h"

#include <optional>

class ExtendedTraceContext : public BasicTraceContext
{
public:
    ExtendedTraceContext(const std::string& funcName,
        const std::optional<std::string>& callContext = std::nullopt,
        const std::optional<std::string>& sourceFile = std::nullopt,
        const std::optional<std::size_t>& lineNum = std::nullopt);

    static std::string extractFileName(const std::string& path);

    std::optional<std::string> getSourceFile() const noexcept;
    void setSourceFile(const std::string& sourceFile) noexcept;
    std::optional<std::size_t> getLineNumber() const noexcept;
    void setLineNumber(const std::size_t lineNumber) noexcept;

private:
    std::optional<std::string> _file;
    std::optional<std::size_t> _line;
};

#endif