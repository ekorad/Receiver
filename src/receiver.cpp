#include <iostream>
#include "ReceiverConfig.h"
#include "Trace.h"

int main()
{
    std::cout << Trace{ "This is a trace!", std::nullopt, LoggingLevel::WARNING };
    return 0;
}