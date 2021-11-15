#include <iostream>
#include "ReceiverConfig.h"
#include "TraceContext.h"

int main()
{
    TraceContext ctxt{ "MyContext" };
    std::cout << ctxt.getContextId().value() << " "
        << ctxt.getSourceLocation().getFunctionName();
    return 0;
}