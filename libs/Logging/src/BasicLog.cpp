/**
 * @file BasicLog.cpp
 * @author Vlad Zahiu (vladzahiu28@gmail.com)
 * @brief Implements the BasicLog class.
 * @version 0.1
 * @date 2021-11-14
 * 
 * @copyright Copyright (c) 2021
 */
#include "BasicLog.h"

BasicLog::BasicLog(const std::string& msg)
    : _msg{ msg } {}

std::string BasicLog::getMessage() const noexcept
{
    return _msg;
}

void BasicLog::setMessage(const std::string& msg) noexcept
{
    _msg = msg;
}

BasicLog::operator std::string() const
{
    return _msg;
}

std::ostream& operator<<(std::ostream& outStream, const BasicLog& log)
{
    outStream << static_cast<std::string>(log);
    return outStream;
}