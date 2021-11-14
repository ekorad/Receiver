#include <iostream>
#include "ReceiverConfig.h"
#include "BasicLog.h"

int main()
{
    std::cout << "Running receiver (version: "
        << Receiver_VERSION_MAJOR << "." << Receiver_VERSION_MINOR << ")\n";

    BasicLog log;
    log = BasicLog{ "Hello, world!" };
    std::cout << log << std::endl;
    return 0;
}