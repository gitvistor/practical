#pragma once
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <vector>
#include "Def.h"
#include "RingBuffer.h"
#include "LogLine.h"

#define LOG_RECODER(level)                             \
    if (level >= Logger::getInstance()->getLogLevel()) \
    LogLine(level, __FILE__, __LINE__)

#define LOG_DEBUG LOG_RECODER(DEBUG)
#define LOG_INFO LOG_RECODER(INFO)
#define LOG_WARN LOG_RECODER(WARN)
#define LOG_ERROR LOG_RECODER(ERROR)
#define LOG_FATAL LOG_RECODER(FATAL)

class Logger
{
public:
    static Logger *getInstance();

    void createFile();

    void setLogLevel(LOG_LEVEL level);
    LOG_LEVEL getLogLevel();

    void flushdata();

    RingBuffer *getBuffer();

private:
    Logger();
    ~Logger();
    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;

private:
    static Logger *m_log;
    static std::once_flag m_onceflag;

    LOG_LEVEL m_level;

    std::atomic_bool threadExit;
    bool threadSync;

    std::thread flushThread;
    std::mutex bufMutex;
    std::mutex condMutex;
    std::condition_variable flushCond;

    uint32_t bufferSize;
    uint32_t consumeSize;
    PSTR outputBuffer;
    std::vector<RingBuffer *> threadBuffers;

    bool isFull;

    FILE *m_file{nullptr};
};