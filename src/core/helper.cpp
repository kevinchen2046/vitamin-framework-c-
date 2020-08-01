
#include <stdio.h>
#include <iostream>
#include <limits>
#include "helper.hpp"
#include "logger.h"
using namespace std;
namespace vitamin
{
    void Helper::logTypes()
    {
        Logger::warn("%s", "---------------------------------------------------------------------");
        Logger::info("类型 \t\t 所占字节数\t\t最大值\t\t最小值");
        Logger::warn("%s", "---------------------------------------------------------------------");
        Logger::grey("bool: \t\t %d %s %d %s %d", sizeof(bool), "\t\t\t", (numeric_limits<bool>::max)(), "\t\t", (numeric_limits<bool>::min)());
        Logger::grey("char: \t\t %d %s %d %s %d", sizeof(char), "\t\t\t", (numeric_limits<char>::max)(), "\t\t", (numeric_limits<char>::min)());
        Logger::grey("signed char: \t %d %s %d %s %d", sizeof(signed char), "\t\t\t", (numeric_limits<signed char>::max)(), "\t\t", (numeric_limits<signed char>::min)());
        Logger::grey("unsigned char: \t %d %s %d %s %d", sizeof(unsigned char), "\t\t\t", (numeric_limits<unsigned char>::max)(), "\t\t", (numeric_limits<unsigned char>::min)());
        Logger::grey("wchar_t: \t\t %d %s %d %s %d", sizeof(wchar_t), "\t\t\t", (numeric_limits<wchar_t>::max)(), "\t\t", (numeric_limits<wchar_t>::min)());
        Logger::grey("short: \t\t %d %s %d %s %d", sizeof(short), "\t\t\t", (numeric_limits<short>::max)(), "\t\t", (numeric_limits<short>::min)());
        Logger::grey("int: \t\t %d %s %d %s %d", sizeof(int), "\t\t\t", (numeric_limits<int>::max)(), "\t", (numeric_limits<int>::min)());
        Logger::grey("unsigned: \t %d %s %d %s %d", sizeof(unsigned), "\t\t\t", (numeric_limits<unsigned>::max)(), "\t\t", (numeric_limits<unsigned>::min)());
        Logger::grey("long: \t\t %d %s %d %s %d", sizeof(long), "\t\t\t", (numeric_limits<long>::max)(), "\t", (numeric_limits<long>::min)());
        Logger::grey("unsigned long: \t %d %s %d %s %d", sizeof(unsigned long), "\t\t\t", (numeric_limits<unsigned long>::max)(), "\t\t", (numeric_limits<unsigned long>::min)());
        Logger::grey("double: \t\t %d %s %d %s %d", sizeof(double), "\t\t\t", (numeric_limits<double>::max)(), "\t\t", (numeric_limits<double>::min)());
        Logger::grey("long double: \t %d %s %d %s %d", sizeof(long double), "\t\t\t", (numeric_limits<long double>::max)(), "\t", (numeric_limits<long double>::min)());
        Logger::grey("float: \t\t %d %s %d %s %d", sizeof(float), "\t\t\t", (numeric_limits<float>::max)(), "\t", (numeric_limits<float>::min)());
        Logger::grey("size_t: \t\t %d %s %d %s %d", sizeof(size_t), "\t\t\t", (numeric_limits<size_t>::max)(), "\t\t", (numeric_limits<size_t>::min)());
        Logger::grey("string: \t\t %d %s %d %s %d", sizeof(string), "\t\t\t", (numeric_limits<string>::max)(), "\t", (numeric_limits<string>::min)());
        Logger::warn("%s", "---------------------------------------------------------------------");
    };
} // namespace vitamin