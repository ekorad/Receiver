#include <iostream>
#include <thread>
#include <mutex>
#include "Logger.h"

#include <atomic>
class SomeClass
{
public:
    SomeClass()
    {
        _logger.log("Created SomeClass");
    }
private:
    Logger _logger{ "SomeClass" };
};

class AnotherClass
{
public:
    AnotherClass()
    {
        _logger.log("Created AnotherClass");
    }
private:
    Logger _logger{ "AnotherClass" };
};

int main()
{
    SomeClass sc;
    AnotherClass ac;
    return 0;
}