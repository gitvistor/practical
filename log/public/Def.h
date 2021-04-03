#pragma once

#define TIMESTR_LEN 32
#define FILENAME_LEN 32
#define HEADSTR_LEN 128
#define FORMAT_LEN 4196
#define LOGMSG_LEN (FORMAT_LEN + TIMESTR_LEN)
#define LOG_LEVEL_NUM 5

enum LOG_LEVEL : uint8_t
{
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL
};

using PCSTR = const char *;
using PSTR = char *;
using UINT32 = unsigned int;
using INT32 = signed int;
using UINT8 = unsigned char;