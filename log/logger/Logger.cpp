#include <sys/time.h>
#include <iostream>
#include "Logger.h"

Logger *Logger::m_log = nullptr;
std::once_flag Logger::m_onceflag;

Logger::Logger()
    : m_level(DEBUG),
      threadExit(false),
      threadSync(false),
      bufferSize(1 << 24),
      isFull(false),
      consumeSize(0)
{
    createFile();
    outputBuffer = new char[bufferSize];
    flushThread = std::move(std::thread(&Logger::flushdata, this));
}

Logger::~Logger()
{
    {
        std::lock_guard<std::mutex> lock(condMutex);
        threadSync = true;
        flushCond.notify_one();
    }

    {
        std::lock_guard<std::mutex> lock(condMutex);
        threadExit = true;
        flushCond.notify_one();
    }

    if (flushThread.joinable())
        flushThread.join();

    free(outputBuffer);

    for (auto &buf : threadBuffers)
        free(buf);

    if (m_file)
    {
        fclose(m_file);
        m_file = nullptr;
    }
}

Logger *Logger::getInstance()
{
    std::call_once(m_onceflag, []() {
        m_log = new Logger();
    });

    return m_log;
}

void Logger::setLogLevel(LOG_LEVEL level)
{
    m_level = level;
}

LOG_LEVEL Logger::getLogLevel()
{
    return m_level;
}

void Logger::createFile()
{
    struct timeval tv = {0, 0};
    gettimeofday(&tv, nullptr);

    struct tm now;
    localtime_r(&tv.tv_sec, &now);

    char filename[FILENAME_LEN];
    snprintf(filename, FILENAME_LEN, "%04d-%02d-%02d.log",
             now.tm_year + 1900,
             now.tm_mon + 1,
             now.tm_mday);

    m_file = fopen(filename, "ab");
}

void Logger::flushdata()
{
    while (!threadExit)
    {
        {
            std::lock_guard<std::mutex> lock(bufMutex);
            for (auto &buf : threadBuffers)
            {
                auto readSize = static_cast<uint32_t>(buf->consumableSize());
                if (consumeSize + readSize >= bufferSize)
                {
                    break;
                }

                if (readSize > 0)
                {
                    auto num = buf->retrieve(outputBuffer + consumeSize, readSize);
                    consumeSize += num;
                }
            }
        }

        if (consumeSize == 0)
        {
            std::unique_lock<std::mutex> lock(condMutex);
            if (threadSync)
            {
                threadSync = false;
                continue;
            }
            
            flushCond.wait_for(lock, std::chrono::microseconds(50));
        }
        else
        {
            fwrite(outputBuffer, sizeof(char), consumeSize, m_file);
            fflush(m_file);
            consumeSize = 0;
        }
    }
}

RingBuffer *Logger::getBuffer()
{
    static thread_local RingBuffer *buf = nullptr;
    if (!buf)
    {
        std::lock_guard<std::mutex> lock(bufMutex);
        buf = new RingBuffer;
        threadBuffers.push_back(buf);
    }
    return buf;
}