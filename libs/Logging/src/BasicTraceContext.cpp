/**
 * @file BasicTraceContext.cpp
 * @author Vlad Zahiu (vladzahiu28@gmail.com)
 * @brief Implements the BasicTraceContext class.
 * @version 0.1
 * @date 2021-11-14
 * 
 * @copyright Copyright (c) 2021
 */

#include "BasicTraceContext.h"

BasicTraceContext::BasicTraceContext(const std::string& funcName,
    const std::optional<std::string> callContext)
    : _func{ funcName }, _callContext{ callContext } {}

std::string BasicTraceContext::getFunctionName() const noexcept
{
    return _func;
}

void BasicTraceContext::setFunctionName(const std::string& funcName) noexcept
{
    _func = funcName;
}

std::optional<std::string> BasicTraceContext::getCallContext() const noexcept
{
    return _callContext;
}

void BasicTraceContext::setCallContext(const std::string& callContext) noexcept
{
    _callContext = callContext;
}