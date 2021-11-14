#include <iostream>
#include "ReceiverConfig.h"
#include "BasicTraceContext.h"

int main()
{
    BasicTraceContext context{ GBTC() };
    std::cout << context.getFunctionName() << std::endl;
    return 0;
}