/**
 * @file SourceLocation.h
 * @author Vlad Zahiu (vladzahiu28@gmail.com)
 * @brief Defines the SourceLocation class.
 * @version 0.1
 * @date 2021-11-14
 * 
 * @copyright Copyright (c) 2021
 */

#ifndef SOURCE_LOCATION_H
#define SOURCE_LOCATION_H

#define getCurrentFunction()        static_cast<std::string>(__builtin_FUNCTION())
#define getCurrentSourceFileName()  \
    SourceLocation::extractFileName(static_cast<std::string>(__builtin_FILE()))
#define getCurrentLineNumber()      static_cast<std::size_t>(__builtin_LINE())

#include <string>

// extract function name and file name

class SourceLocation
{
public:
    SourceLocation(const std::string& funcName = getCurrentFunction(),
        const std::string& sourceFile = getCurrentSourceFileName(),
        const std::size_t lineNum = getCurrentLineNumber());

    static std::string extractFileName(const std::string& path) noexcept;

    std::string getFunctionName() const noexcept;
    void setFunctionName(const std::string& funcName) noexcept;
    std::string getSourceFileName() const noexcept;
    void setSourceFileName(const std::string& sourceFile) noexcept;
    std::size_t getLineNumber() const noexcept;
    void setLineNumber(const std::size_t lineNum) noexcept;

private:
    std::string _func;
    std::string _file;
    std::size_t _line;
};

#endif