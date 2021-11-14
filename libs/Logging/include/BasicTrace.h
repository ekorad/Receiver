/**
 * @file BasicTrace.h
 * @author Vlad Zahiu (vladzahiu28@gmail.com)
 * @brief Defines the BasicTrace class.
 * @version 0.1
 * @date 2021-11-14
 * 
 * @copyright Copyright (c) 2021
 */

#ifndef BASIC_TRACE_H
#define BASIC_TRACE_H

#include <string>
#include <ostream>

class BasicTrace
{
public:
    BasicTrace(const std::string& msg = "");

    std::string getMessage() const noexcept;
    void setMessage(const std::string& msg) noexcept;

    virtual explicit operator std::string() const;

    friend std::ostream& operator<<(std::ostream& outStream,
        const BasicTrace& log);

private:
    std::string _msg;
};

#endif