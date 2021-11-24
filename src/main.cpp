#include <iostream>
#include <thread>
#include <mutex>
#include "ArgumentsParser.h"
#include "SocketClient.h"

int main(int argc, char* argv[])
{
    ArgumentsParser argParser{ argc, argv };
    SocketClient client;
    try
    {
        client.connect(argParser.getIPAddress(), argParser.getPort());
        std::cout << "s";
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}