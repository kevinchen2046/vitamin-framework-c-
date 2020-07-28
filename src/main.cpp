#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <limits>
#include "person.h"
#include "core/helper.h"

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

    string str = "Hello";
    string megestr = str + "World!";
    printf("> merge: %s , enum:%d %s", megestr.c_str(), Color::blue, "\n");
    printf("> str: %s , length:%d %s", str.c_str(), str.length(), "\n");

    Helper::logTypes();

    Person person;
    person.age = 20;
    person.name = "Kevin Chen";
    person.sex = "Men";
    person.say();

    system("pause");
    return 0;
}