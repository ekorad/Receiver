/**
 * @file ITraceComponent.cpp
 * @author Vlad Zahiu (vladzahiu28@gmail.com)
 * @brief Implements functionality related to the ITraceComponent interface.
 * @version 0.1
 * @date 2021-11-15
 * 
 * @copyright Copyright (c) 2021
 */

#include "ITraceComponent.h"

std::ostream& operator<<(std::ostream& outStream, const ITraceComponent& comp)
{
    outStream << static_cast<std::string>(comp);
    return outStream;
}