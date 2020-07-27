
#include <stdio.h>
#include <iostream>
#include <limits>
#include "helper.h"

using namespace std;

void Helper::logTypes()
{
    printf("%s %s", "---------------------------------------------------------------------", "\n");
    printf("类型 \t\t 所占字节数\t\t最大值\t\t最小值\n");
    printf("%s %s", "---------------------------------------------------------------------", "\n");
    printf("bool: \t\t %d %s %d %s %d %s", sizeof(bool), "\t\t\t", (numeric_limits<bool>::max)(), "\t\t", (numeric_limits<bool>::min)(), "\n");
    printf("char: \t\t %d %s %d %s %d %s", sizeof(char), "\t\t\t", (numeric_limits<char>::max)(), "\t\t", (numeric_limits<char>::min)(), "\n");
    printf("signed char: \t %d %s %d %s %d %s", sizeof(signed char), "\t\t\t", (numeric_limits<signed char>::max)(), "\t\t", (numeric_limits<signed char>::min)(), "\n");
    printf("unsigned char: \t %d %s %d %s %d %s", sizeof(unsigned char), "\t\t\t", (numeric_limits<unsigned char>::max)(), "\t\t", (numeric_limits<unsigned char>::min)(), "\n");
    printf("wchar_t: \t %d %s %d %s %d %s", sizeof(wchar_t), "\t\t\t", (numeric_limits<wchar_t>::max)(), "\t\t", (numeric_limits<wchar_t>::min)(), "\n");
    printf("short: \t\t %d %s %d %s %d %s", sizeof(short), "\t\t\t", (numeric_limits<short>::max)(), "\t\t", (numeric_limits<short>::min)(), "\n");
    printf("int: \t\t %d %s %d %s %d %s", sizeof(int), "\t\t\t", (numeric_limits<int>::max)(), "\t", (numeric_limits<int>::min)(), "\n");
    printf("unsigned: \t %d %s %d %s %d %s", sizeof(unsigned), "\t\t\t", (numeric_limits<unsigned>::max)(), "\t\t", (numeric_limits<unsigned>::min)(), "\n");
    printf("long: \t\t %d %s %d %s %d %s", sizeof(long), "\t\t\t", (numeric_limits<long>::max)(), "\t", (numeric_limits<long>::min)(), "\n");
    printf("unsigned long: \t %d %s %d %s %d %s", sizeof(unsigned long), "\t\t\t", (numeric_limits<unsigned long>::max)(), "\t\t", (numeric_limits<unsigned long>::min)(), "\n");
    printf("double: \t %d %s %d %s %d %s", sizeof(double), "\t\t\t", (numeric_limits<double>::max)(), "\t\t", (numeric_limits<double>::min)(), "\n");
    printf("long double: \t %d %s %d %s %d %s", sizeof(long double), "\t\t\t", (numeric_limits<long double>::max)(), "\t", (numeric_limits<long double>::min)(), "\n");
    printf("float: \t\t %d %s %d %s %d %s", sizeof(float), "\t\t\t", (numeric_limits<float>::max)(), "\t", (numeric_limits<float>::min)(), "\n");
    printf("size_t: \t %d %s %d %s %d %s", sizeof(size_t), "\t\t\t", (numeric_limits<size_t>::max)(), "\t\t", (numeric_limits<size_t>::min)(), "\n");
    printf("string: \t %d %s %d %s %d %s", sizeof(string), "\t\t\t", (numeric_limits<string>::max)(), "\t", (numeric_limits<string>::min)(), "\n");
    printf("%s %s", "---------------------------------------------------------------------", "\n");
};