#include <iostream>
#include "ReceiverConfig.h"
#include "TimestampedTrace.h"

int main()
{
    std::cout << "Running receiver (version: "
        << Receiver_VERSION_MAJOR << "." << Receiver_VERSION_MINOR << ")\n";

    TimestampedTrace log{ "Hello, world!" };
    log = TimestampedTrace{ "Some other message!" };
    std::cout << log << std::endl;
    return 0;
}