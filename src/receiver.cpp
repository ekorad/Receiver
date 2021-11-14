#include <iostream>
#include "ReceiverConfig.h"
#include "TimestampedLog.h"

int main()
{
    std::cout << "Running receiver (version: "
        << Receiver_VERSION_MAJOR << "." << Receiver_VERSION_MINOR << ")\n";

    TimestampedLog log{ "Hello, world!" };
    log = TimestampedLog{ "Some other message!" };
    std::cout << log << std::endl;
    return 0;
}