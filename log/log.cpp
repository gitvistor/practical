#include "log.h"
#include <cstdarg>
#include <cstring>
#include <thread>
#include <ctime>
#include <sys/time.h>

Logger *Logger::m_log = nullptr;
std::once_flag Logger::m_onceflag;

Logger::Logger()
{
    init(LEVEL_INFO, TARGET_FILE);
}

Logger::~Logger()
{
    uninit();
}

void Logger::init(LOG_LEVEL level, LOG_TARGET target)
{
    setLogLevel(level);
    setLogTarget(target);
    createFile();
}

void Logger::uninit()
{
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

PCSTR Logger::getLogLevel(LOG_LEVEL level)
{
    switch (level)
    {
    case LEVEL_INFO:
        return "Info";
    case LEVEL_DEBUG:
        return "Debug";
    case LEVEL_WARNING:
        return "Warning";
    case LEVEL_ERROR:
        return "Error";
    case LEVEL_FATAL:
        return "Fatal";
    default:
        break;
    }
    return "None";
}

void Logger::setLogTarget(LOG_TARGET target)
{
    m_target = target;
}

int Logger::createFile()
{
    time_t now = time(nullptr);
    struct tm *tmstr = localtime(&now);
    char filename[128];
    // snprintf(filename, sizeof(filename), "%04d-%02d-%02d.%02d:%02d:%02d.log",
    snprintf(filename, sizeof(filename), "%04d-%02d-%02d.log",
             tmstr->tm_year + 1900,
             tmstr->tm_mon + 1,
             tmstr->tm_mday,
             tmstr->tm_hour,
             tmstr->tm_min,
             tmstr->tm_sec);

    m_file = fopen(filename, "at+");

    return 0;
}

void Logger::GetTimeString(PSTR pTimeStr, UINT32 len)
{
    if (!pTimeStr || len <= 0)
        return;

    time_t tCurrentTime = time(NULL);

    struct tm tSysTime;
    localtime_r(&tCurrentTime, &tSysTime);

    struct timeval tTimeVal;
    gettimeofday(&tTimeVal, NULL);

    snprintf(pTimeStr, len, "%04d-%02d-%02d %02d:%02d:%02d.%06d",
             tSysTime.tm_year + 1900,
             tSysTime.tm_mon + 1,
             tSysTime.tm_mday,
             tSysTime.tm_hour,
             tSysTime.tm_min,
             tSysTime.tm_sec,
             tTimeVal.tv_usec);
}

void Logger::Log(LOG_LEVEL level, PCSTR file, INT32 line, PCSTR logmsg, ...)
{
    char timeStr[64];
    GetTimeString(timeStr, sizeof(timeStr) / sizeof(char));

    char msg[4196] = {0};
    va_list va;
    va_start(va, logmsg);
    snprintf(msg, sizeof(msg) / sizeof(char), logmsg, va);
    va_end(va);

    char content[4196 + 64];
    snprintf(content, sizeof(content) / sizeof(char), "[%s][%u][%s][%s:%u]%s\n",
             getLogLevel(level),
             std::this_thread::get_id(),
             timeStr,
             file,
             line,
             msg);

    fwrite(content, sizeof(char), strlen(content), m_file);
}