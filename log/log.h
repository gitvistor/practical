#pragma once
#include <cstdio>
#include <mutex>

#define TIMESTR_LEN 64
#define FORMAT_LEN 4196
#define LOGMSG_LEN (FORMAT_LEN + TIMESTR_LEN)
#define LOG_LEVEL_NUM 5

enum LOG_LEVEL
{
    LEVEL_DEBUG = 0,
    LEVEL_INFO,
    LEVEL_WARNING,
    LEVEL_ERROR,
    LEVEL_FATAL
};

enum LOG_TARGET
{
    TARGET_NONE = 0x00,
    TARGET_CONSOLE = 0x01,
    TARGET_FILE = 0x10,
};

using PCSTR = const char *;
using PSTR = char *;
using UINT32 = unsigned int;
using INT32 = signed int;
using UINT8 = unsigned char;

#define LOG_Debug(...) Logger::getInstance()->Log(LEVEL_DEBUG, __FILE__, __LINE__, ##__VA_ARGS__)
#define LOG_INFO(...) Logger::getInstance()->Log(LEVEL_INFO, __FILE__, __LINE__, ##__VA_ARGS__)
#define LOG_Warning(...) Logger::getInstance()->Log(LEVEL_WARNING, __FILE__, __LINE__, ##__VA_ARGS__)
#define LOG_ERROR(...) Logger::getInstance()->Log(LEVEL_ERROR, __FILE__, __LINE__, ##__VA_ARGS__)
#define LOG_FATAL(...) Logger::getInstance()->Log(LEVEL_FATAL, __FILE__, __LINE__, ##__VA_ARGS__)

class Logger
{
public:
    static Logger *getInstance();

    void init(LOG_LEVEL level, LOG_TARGET target);
    void uninit();
    int createFile();

    void setLogLevel(LOG_LEVEL level);

    void setLogTarget(LOG_TARGET target);

    void Log(LOG_LEVEL level, PCSTR file, INT32 line, PCSTR logmsg, ...);

private:
    Logger();
    ~Logger();
    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;

private:
    static Logger *m_log;
    static std::once_flag m_onceflag;

    LOG_LEVEL m_level;
    LOG_TARGET m_target;

    FILE *m_file{nullptr};
};