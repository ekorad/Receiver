/**
 * @file TraceLevelComponent.h
 * @author Vlad Zahiu (vladzahiu28@gmail.com)
 * @brief Defines the TraceLevelComponent class.
 * @version 0.1
 * @date 2021-11-15
 * 
 * @copyright Copyright (c) 2021
 */

#ifndef TRACE_LEVEL_H
#define TRACE_LEVEL_H

#include "ITraceComponent.h"
#include "LoggingLevel.h"

class TraceLevelComponent : virtual public ITraceComponent
{
public:
    TraceLevelComponent(const LoggingLevel& level = LoggingLevel::INFO);

    LoggingLevel getLevel() const noexcept;
    void setLevel(const LoggingLevel level);

    explicit operator std::string() const override;

private:
    LoggingLevel _level;
};

#endif