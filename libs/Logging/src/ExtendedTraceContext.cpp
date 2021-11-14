/**
 * @file ExtendedTraceContext.cpp
 * @author Vlad Zahiu (vladzahiu28@gmail.com)
 * @brief Implements the ExtendedTraceContext class. 
 * @version 0.1
 * @date 2021-11-14
 * 
 * @copyright Copyright (c) 2021
 */

#include "ExtendedTraceContext.h"

ExtendedTraceContext::ExtendedTraceContext(const std::string& funcName,
        const std::optional<std::string>& callContext,
        const std::optional<std::string>& sourceFile,
        const std::optional<std::size_t>& lineNum)
    : BasicTraceContext{ funcName, callContext },
    _file{ sourceFile },
    _line{ lineNum } {}

std::string ExtendedTraceContext::extractFileName(const std::string& path)
{
    const auto foundIndex = path.find_last_of("/");
    if (foundIndex == std::string::npos)
    {
        return path;
    }
    else
    {
        return path.substr(foundIndex + 1);
    }
}

std::optional<std::string> ExtendedTraceContext::getSourceFile() const noexcept
{
    return _file;
}

void ExtendedTraceContext::setSourceFile(const std::string& sourceFile)
    noexcept
{
    _file = sourceFile;
}

std::optional<std::size_t> ExtendedTraceContext::getLineNumber() const noexcept
{
    return _line;
}

void ExtendedTraceContext::setLineNumber(const std::size_t lineNumber) noexcept
{
    _line = lineNumber;
}