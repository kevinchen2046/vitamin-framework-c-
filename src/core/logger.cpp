#include <iostream>
#include <stdarg.h>
#include <windows.h>
#include "logger.h"
using namespace std;

std::string &getFormattedStr(std::string &strFormatted, const char *strFormat, va_list arglist)
{
  const int MAX_FORMATTED_STR_LEN = 2048;
  char strResult[MAX_FORMATTED_STR_LEN] = {0};
  vsprintf_s(strResult, strFormat, arglist);
  strFormatted = strResult;
  return strFormatted;
}
void Logger::line(const char *__format, ...)
{
  int total = 60;
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
  std::string strLog;
  va_list arglist;
  va_start(arglist, __format);
  string result = getFormattedStr(strLog, __format, arglist);
  int rlen = result.length();
  int half = ((total - rlen) / 2) >> 0;
  string line = "";
  for (int i = 0; i < half; i++)
  {
    line += "-";
  }
  strLog = "[INF] " + line + result + line;
  va_end(arglist);
  std::cout << strLog << std::endl;
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
void Logger::grey(const char *__format, ...)
{
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
  std::string strLog;
  va_list arglist;
  va_start(arglist, __format);
  strLog = "[LOG] " + getFormattedStr(strLog, __format, arglist);
  va_end(arglist);
  std::cout << strLog << std::endl;
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void Logger::log(const char *__format, ...)
{
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
  std::string strLog;
  va_list arglist;
  va_start(arglist, __format);
  strLog = "[LOG] " + getFormattedStr(strLog, __format, arglist);
  va_end(arglist);
  std::cout << strLog << std::endl;
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void Logger::info(const char *__format, ...)
{
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
  std::string strLog;
  va_list arglist;
  va_start(arglist, __format);
  strLog = "[INF] " + getFormattedStr(strLog, __format, arglist);
  va_end(arglist);
  std::cout << strLog << std::endl;
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void Logger::warn(const char *__format, ...)
{
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN);
  std::string strLog;
  va_list arglist;
  va_start(arglist, __format);
  strLog = "[WAR] " + getFormattedStr(strLog, __format, arglist);
  va_end(arglist);
  std::cout << strLog << std::endl;
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void Logger::debug(const char *__format, ...)
{
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
  std::string strLog;
  va_list arglist;
  va_start(arglist, __format);
  strLog = "[DEB] " + getFormattedStr(strLog, __format, arglist);
  va_end(arglist);
  std::cout << strLog << std::endl;
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void Logger::error(const char *__format, ...)
{
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
  std::string strLog;
  va_list arglist;
  va_start(arglist, __format);
  strLog = "[ERR] " + getFormattedStr(strLog, __format, arglist);
  va_end(arglist);
  std::cout << strLog << std::endl;
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}