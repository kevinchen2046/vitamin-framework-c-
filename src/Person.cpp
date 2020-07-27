#include <iostream>
#include "Person.h"

using namespace std;

Person::Person()
{
    printf("创建了一个新的对象！");
}

void Person::say()
{
    printf("大家好，我叫 %s ,性别 %s ,今年 %d 岁. %s", name, sex, age, "\n");
}