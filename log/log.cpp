#include "log.h"
#include <cstdarg>
#include <cstring>
#include <ctime>
#include <unistd.h>
#include <sys/time.h>
#include <sys/syscall.h>

Logger *Logger::m_log = nullptr;
std::once_flag Logger::m_onceflag;

PCSTR logLevelNames[LOG_LEVEL_NUM] = {"Debug", "Info", "Warning", "Error", "Fatal"};

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

void Logger::setLogTarget(LOG_TARGET target)
{
    m_target = target;
}

int Logger::createFile()
{
    struct timeval tv = {0, 0};
    gettimeofday(&tv, nullptr);

    struct tm now;
    localtime_r(&tv.tv_sec, &now);

    char filename[FORMAT_LEN];
    snprintf(filename, sizeof(filename), "%04d-%02d-%02d.log",
             now.tm_year + 1900,
             now.tm_mon + 1,
             now.tm_mday);

    m_file = fopen(filename, "at+");

    return 0;
}

void Logger::Log(LOG_LEVEL level, PCSTR file, INT32 line, PCSTR format, ...)
{
    static thread_local pid_t tid = 0;
    if (tid == 0)
    {
        tid = syscall(__NR_gettid);
    }
    
    struct timeval tv = {0, 0};
    gettimeofday(&tv, nullptr);

    struct tm now;
    localtime_r(&tv.tv_sec, &now);

    char timeStr[TIMESTR_LEN];
    snprintf(timeStr, TIMESTR_LEN, "%04d-%02d-%02d %02d:%02d:%02d.%06ld",
             now.tm_year + 1900,
             now.tm_mon + 1,
             now.tm_mday,
             now.tm_hour,
             now.tm_min,
             now.tm_sec,
             tv.tv_usec);

    char formatStr[FORMAT_LEN] = {0};
    va_list va;
    va_start(va, format);
    snprintf(formatStr, FORMAT_LEN, format, va);
    va_end(va);

    char logmsg[LOGMSG_LEN];
    snprintf(logmsg, LOGMSG_LEN, "[%c %s %u %s:%d]%s\n",
             logLevelNames[static_cast<int>(level)][0],
             timeStr,
             tid,
             file,
             line,
             formatStr);

    fwrite(logmsg, sizeof(char), strlen(logmsg), m_file);
}