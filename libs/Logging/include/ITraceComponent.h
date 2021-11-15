/**
 * @file ITraceComponent.h
 * @author Vlad Zahiu (vladzahiu28@gmail.com)
 * @brief Defines the ITraceComponent interface.
 * @version 0.1
 * @date 2021-11-15
 * 
 * @copyright Copyright (c) 2021
 */

#ifndef ITRACE_COMPONENT_H
#define ITRACE_COMPONENT_H

#include <string>
#include <ostream>

class ITraceComponent
{
public:
    virtual explicit operator std::string() const = 0;

    friend std::ostream& operator<<(std::ostream& outStream,
        const ITraceComponent& comp);
};

#endif