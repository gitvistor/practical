#pragma once
#include "Logger.h"

class LogLine
{
public:
  LogLine(LOG_LEVEL level, const char *file, uint32_t line);

  ~LogLine();

  LogLine &operator<<(bool data);

  LogLine &operator<<(char data);

  LogLine &operator<<(int16_t data);

  LogLine &operator<<(uint16_t data);

  LogLine &operator<<(int32_t data);

  LogLine &operator<<(uint32_t data);

  LogLine &operator<<(int64_t data);

  LogLine &operator<<(uint64_t data);

  LogLine &operator<<(float data);

  LogLine &operator<<(double data);

  LogLine &operator<<(const char *data);

  LogLine &operator<<(const std::string &str);

private:
  void append(const char *data, size_t len);

private:
  size_t count;
};