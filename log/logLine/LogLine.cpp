
#include "LogLine.h"
#include "Utility.h"
#include "NumToString.h"

static PCSTR logLevelNames[LOG_LEVEL_NUM] = {"Debug", "Info", "Warning", "Error", "Fatal"};

LogLine::LogLine(LOG_LEVEL level, const char *file, uint32_t line) : count(0)
{
  char timeStr[TIMESTR_LEN];
  detail::getTimeStr(timeStr);

  char headstr[HEADSTR_LEN];
  snprintf(headstr, HEADSTR_LEN, "[%c %s %u %s:%u]",
           logLevelNames[static_cast<int>(level)][0],
           timeStr,
           static_cast<uint32_t>(detail::gettid()),
           file,
           line);
          
  append(headstr, strlen(headstr));

  // *this << '[' << logLevelNames[static_cast<int>(level)][0] << ' ' << detail::getTimeStr(timeStr)
  //       << ' ' << detail::gettid() << ' ' << file << ':' << line << ']';
}

LogLine::~LogLine()
{
  *this << '\n';
  Logger::getInstance()->getBuffer()->incConsumablePos(count);
}

LogLine &LogLine::operator<<(bool data)
{
  if (data)
    append("true", 4);
  else
    append("false", 5);
  return *this;
}

LogLine &LogLine::operator<<(char data)
{
  append(&data, 1);
  return *this;
}

LogLine &LogLine::operator<<(int16_t data)
{
  char tmp[8];
  size_t len = detail::i16toa(data, tmp);
  append(tmp, len);
  return *this;
}

LogLine &LogLine::operator<<(uint16_t data)
{
  char tmp[8];
  size_t len = detail::u16toa(data, tmp);
  append(tmp, len);
  return *this;
}

LogLine &LogLine::operator<<(int32_t data)
{
  char tmp[12];
  size_t len = detail::i32toa(data, tmp);
  append(tmp, len);
  return *this;
}

LogLine &LogLine::operator<<(uint32_t data)
{
  char tmp[12];
  size_t len = detail::u32toa(data, tmp);
  append(tmp, len);
  return *this;
}

LogLine &LogLine::operator<<(int64_t data)
{
  char tmp[24];
  size_t len = detail::i64toa(data, tmp);
  append(tmp, len);
  return *this;
}

LogLine &LogLine::operator<<(uint64_t data)
{
  char tmp[24];
  size_t len = detail::u64toa(data, tmp);
  append(tmp, len);
  return *this;
}

LogLine &LogLine::operator<<(float data)
{
  auto str = std::move(std::to_string(data));
  append(str.data(), str.length());
  return *this;
}

LogLine &LogLine::operator<<(double data)
{
  auto str = std::move(std::to_string(data));
  append(str.data(), str.length());
  return *this;
}

LogLine &LogLine::operator<<(const char *data)
{
  append(data, strlen(data));
  return *this;
}

LogLine &LogLine::operator<<(const std::string &str)
{
  append(str.data(), str.length());
  return *this;
}

void LogLine::append(const char *data, size_t len)
{
  Logger::getInstance()->getBuffer()->append(data, len);
  count += len;
}