#ifndef VITAMIN_BASE
#define VITAMIN_BASE
#include <iostream>
#include <typeinfo>
#include <cxxabi.h>
using namespace std;

string bool_to_str(int value)
{
    return value > 0 ? "true" : "false";
}

string getRealClassName(const char *name)
{
    int status;
    char *real_name;
    real_name = abi::__cxa_demangle(name, nullptr, nullptr, &status);
    string s(real_name);
    free(real_name);
    real_name = nullptr;
    return s;
}

template <typename T>
string getDefineName()
{
    return getRealClassName(typeid(T).name());
}

template <typename T>
string getDefineName(T val)
{
    return getRealClassName(typeid(val).name());
}
#endif