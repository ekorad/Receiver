/**
 * @file TraceMessageComponent.h
 * @author Vlad Zahiu (vladzahiu28@gmail.com)
 * @brief Defines the TraceMessageComponent class.
 * @version 0.2
 * @date 2021-11-14
 * 
 * @copyright Copyright (c) 2021
 */

#ifndef TRACE_MESSAGE_H
#define TRACE_MESSAGE_H

#include "ITraceComponent.h"

#include <string>
#include <ostream>

class TraceMessageComponent : virtual public ITraceComponent
{
public:
    TraceMessageComponent(const std::string& msg = "");

    std::string getMessage() const noexcept;
    void setMessage(const std::string& msg) noexcept;

    explicit operator std::string() const override;

private:
    std::string _msg;
};

#endif