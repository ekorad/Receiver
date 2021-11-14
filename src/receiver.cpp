#include <iostream>
#include "ReceiverConfig.h"
#include "ExtendedTraceContext.h"

int main()
{
    ExtendedTraceContext context{ GETC() };
    std::cout << context.getSourceFile().value() << std::endl;
    return 0;
}