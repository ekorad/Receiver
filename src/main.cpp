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
        client.enableServerWait(true);
        client.connect(argParser.getIPAddress(), argParser.getPort());
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}