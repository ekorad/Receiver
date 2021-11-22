#include <iostream>
#include <thread>
#include <mutex>
#include "ArgumentsParser.h"
#include "SocketClient.h"

int main(int argc, char* argv[])
{
    ArgumentsParser argParser{ argc, argv };
    SocketClient client{ argParser.getIPAddress(), argParser.getPort() };
    return 0;
}