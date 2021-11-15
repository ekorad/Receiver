/**
 * @file TraceMessageComponent.cpp
 * @author Vlad Zahiu (vladzahiu28@gmail.com)
 * @brief Implements the TraceMessageComponent class.
 * @version 0.2
 * @date 2021-11-14
 * 
 * @copyright Copyright (c) 2021
 */
#include "TraceMessageComponent.h"

TraceMessageComponent::TraceMessageComponent(const std::string& msg)
    : _msg{ msg } {}

std::string TraceMessageComponent::getMessage() const noexcept
{
    return _msg;
}

void TraceMessageComponent::setMessage(const std::string& msg) noexcept
{
    _msg = msg;
}

TraceMessageComponent::operator std::string() const
{
    return _msg;
}