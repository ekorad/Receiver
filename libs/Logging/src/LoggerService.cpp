#include "LoggerService.h"

LoggerService::~LoggerService()
{
    stop();
}

LoggerService& LoggerService::getInstance()
{
    static std::mutex accessMutex;
    static LoggerService instance;

    std::lock_guard<std::mutex> lock{ accessMutex };
    return instance;
}

void LoggerService::start()
{
    const auto streamMode = std::ofstream::out
        | (_fileAppend ? std::ofstream::app : std::ofstream::trunc);

    std::lock_guard<std::mutex> lock{ _mutex };

    if (_shutdownRequested != ShutdownRequest::NONE)
    {
        throw std::runtime_error("Cannot start service during shutdown");
    }

    if (!_operational)
    {
        _outStream.open(_fileName, streamMode);
        if (_outStream.fail())
        {
            throw std::system_error(errno, std::system_category(),
                "Could not open log file for writing");
        }

        try
        {
            _loggingThread = std::thread{ &LoggerService::loggingThreadFunc, this };
            _operational = true;
        }
        catch (const std::system_error& error)
        {
            throw std::system_error(error.code().value(),
                std::system_category(), "Could not start service thread");
        }
    }
    else
    {
        throw std::runtime_error("Service already started");
    }
}

void LoggerService::pause()
{
    std::lock_guard<std::mutex> lock{ _mutex };

    if (_operational)
    {
        _pauseRequested = true;
    }
    else
    {
        throw std::runtime_error("Service is not operational");
    }
}

void LoggerService::resume()
{
    std::lock_guard<std::mutex> lock{ _mutex };

    if (_operational)
    {
        _pauseRequested = false;
    }
    else
    {
        throw std::runtime_error("Service is not operational");
    }
}

void LoggerService::stop(const bool flush) noexcept
{
    std::unique_lock<std::mutex> lock{ _mutex };

    if (_operational)
    {
        _operational = false;
        _shutdownRequested = (flush ? ShutdownRequest::GRACEFUL : ShutdownRequest::FORCEFUL);
        lock.unlock();
        _loggingThread.value().join();

        _outStream.close();
        _loggingThread = std::nullopt;
        _shutdownRequested = ShutdownRequest::NONE;
        _pauseRequested = false;
    }
}

bool LoggerService::isOperational() const noexcept
{
    std::lock_guard<std::mutex> lock{ _mutex };
    return _operational;
}

bool LoggerService::isPaused() const noexcept
{
    std::unique_lock<std::mutex> lock{ _mutex };
    return _pauseRequested;
}

void LoggerService::setLogFileName(const std::string& fileName)
{
    std::lock_guard<std::mutex> lock{ _mutex };

    if (_operational || _outStream.is_open())
    {
        throw std::runtime_error{ "Cannot change log file when service is operational" };
    }

    _fileName = fileName;
}

std::string LoggerService::getLogFileName() const noexcept
{
    std::lock_guard<std::mutex> lock{ _mutex };
    return _fileName;
}

void LoggerService::enableFileAppend(const bool enabled)
{
    std::lock_guard<std::mutex> lock{ _mutex };

    if (_operational || _outStream.is_open())
    {
        throw std::runtime_error{ "Cannot change log file append mode when service is operational" };
    }

    _fileAppend = true;
}

bool LoggerService::fileAppendEnabled() const noexcept
{
    std::lock_guard<std::mutex> lock{ _mutex };
    return _fileAppend;
}

const std::string LoggerService::defaultFileName = "out.log";

void LoggerService::loggingThreadFunc()
{
    constexpr auto waitDuration = std::chrono::milliseconds(100);
    constexpr std::size_t maxBatchSize = 100;
    const auto waitPredicate = [this]()
    {
        if (this->_shutdownRequested != ShutdownRequest::NONE)
        {
            return true;
        }

        if (this->_pauseRequested)
        {
            return false;
        }

        return !this->_traceQueue.empty();
    };
    bool gracefulShutdownAck = false;

    while (true)
    {
        std::unique_lock<std::mutex> lock{ _mutex };
        while (_condVar.wait_for(lock, waitDuration, waitPredicate) == false);

        if (_shutdownRequested == ShutdownRequest::FORCEFUL)
        {
            lock.unlock();
            break;
        }
        else if (!gracefulShutdownAck && (_shutdownRequested == ShutdownRequest::GRACEFUL))
        {
            gracefulShutdownAck = true;
        }

        if (!_traceQueue.empty())
        {
            const auto availableBatchSize = _traceQueue.size();
            const auto sendBatchSize = (availableBatchSize > maxBatchSize)
                ? maxBatchSize : availableBatchSize;
            std::vector<std::unique_ptr<TrivialLogTrace>> tmpTraces;

            tmpTraces.insert(tmpTraces.end(),
                std::make_move_iterator(_traceQueue.begin()),
                std::make_move_iterator(_traceQueue.begin() + sendBatchSize));
            _traceQueue.erase(_traceQueue.begin(), _traceQueue.begin() + sendBatchSize);

            lock.unlock();

            for (decltype(tmpTraces.size()) i = 0; i < tmpTraces.size(); i++)
            {
                _outStream << static_cast<std::string>(*tmpTraces[i]) << std::endl;
            }
        }
        else
        {
            lock.unlock();
            if (gracefulShutdownAck)
            {
                break;
            }
        }
    }
}