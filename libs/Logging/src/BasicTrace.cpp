/**
 * @file BasicTrace.cpp
 * @author Vlad Zahiu (vladzahiu28@gmail.com)
 * @brief Implements the BasicTrace class.
 * @version 0.1
 * @date 2021-11-14
 * 
 * @copyright Copyright (c) 2021
 */
#include "BasicTrace.h"

BasicTrace::BasicTrace(const std::string& msg)
    : _msg{ msg } {}

std::string BasicTrace::getMessage() const noexcept
{
    return _msg;
}

void BasicTrace::setMessage(const std::string& msg) noexcept
{
    _msg = msg;
}

BasicTrace::operator std::string() const
{
    return _msg;
}

std::ostream& operator<<(std::ostream& outStream, const BasicTrace& log)
{
    outStream << static_cast<std::string>(log);
    return outStream;
}