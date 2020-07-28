#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <limits>
#include "person.h"
#include "core/helper.h"
#include "core/logger.h"
using namespace std;

enum Color
{
    red,
    green,
    blue
};

int main()
{
    //支持UTF8，防止中文乱码
    system("chcp 65001");
    Helper::logTypes();

    string str = "Hello";
    string megestr = str + "World!";
    Logger::info("> merge: %s , enum:%d", megestr.c_str(), Color::blue);
    //printf("> str: %s , length:%d %s", str.c_str(), str.length(), "\n");
    Logger::log("> str: %s , length:%d", str.c_str(), str.length());
    

    Person person;
    person.age = 20;
    person.name = "Kevin Chen";
    person.sex = "Men";
    person.say();

    system("pause");
    return 0;
}