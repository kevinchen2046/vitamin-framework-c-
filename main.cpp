#include <stdio.h>
#include <windows.h>

#include <iostream>
#include <limits>
#include "src/Person.h"
#include "src/core/helper.h"

using namespace std;

enum Color
{
    red,
    green,
    blue
};

int main()
{
    system("chcp 65001");
    printf("Hello World\n");

    char a[] = "12121";
    string str = "dfdfdf\n";
    printf(strcat(a, "\n"));
    printf("> %s %d %s", str.data(), str.length(), "\n");

    Helper::logTypes();

    Person xc;
    xc.age = 18;
    xc.name = "X";
    xc.sex = "M";
    xc.say();
    
    system("pause");
    return 0;
}