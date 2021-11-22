/**
 * @file SourceLocation.cpp
 * @author Vlad Zahiu (vladzahiu28@gmail.com)
 * @brief Implements the SourceLocation class.
 * @version 0.1
 * @date 2021-11-15
 * 
 * @copyright Copyright (c) 2021
 */

#include "SourceLocation.h"

#ifdef _WIN32
static constexpr char pathDelimiter = '\\';
#else
static constexpr char pathDelimiter = '/';
#endif

SourceLocation::SourceLocation(const std::string& funcName,
    const std::string& sourceFile, const std::size_t lineNum)
    : _func{ funcName }, _file{ sourceFile }, _line{ lineNum } {}

std::string SourceLocation::extractFileName(const std::string& path) noexcept
{
    const auto foundIndex = path.find_last_of(pathDelimiter);
    if (foundIndex == std::string::npos)
    {
        return path;
    }
    else
    {
        return path.substr(foundIndex + 1);
    }
}

std::string SourceLocation::getFunctionName() const noexcept
{
    return _func;
}

void SourceLocation::setFunctionName(const std::string& funcName) noexcept
{
    _func = funcName;
}

std::string SourceLocation::getSourceFileName() const noexcept
{
    return _file;
}

void SourceLocation::setSourceFileName(const std::string& sourceFile) noexcept
{
    _file = sourceFile;
}

std::size_t SourceLocation::getLineNumber() const noexcept
{
    return _line;
}

void SourceLocation::setLineNumber(const std::size_t lineNum) noexcept
{
    _line = lineNum;
}