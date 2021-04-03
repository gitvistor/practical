#pragma once

#include <cstring>
#include <unistd.h>
#include <sys/time.h>
#include <sys/syscall.h>
#include "Def.h"

namespace detail
{
  static pid_t gettid()
  {
    static thread_local pid_t tid = 0;
    if (tid == 0)
    {
      tid = syscall(__NR_gettid);
    }

    return tid;
  }

  static const char *getTimeStr(char *str)
  {
    struct timeval tv = {0, 0};
    gettimeofday(&tv, nullptr);

    struct tm now;
    localtime_r(&tv.tv_sec, &now);

    snprintf(str, TIMESTR_LEN, "%04d-%02d-%02d %02d:%02d:%02d.%06ld",
             now.tm_year + 1900,
             now.tm_mon + 1,
             now.tm_mday,
             now.tm_hour,
             now.tm_min,
             now.tm_sec,
             tv.tv_usec);
    return str;
  }

} // namespace detail