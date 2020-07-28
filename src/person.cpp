#include <iostream>
#include "person.h"

Person::Person(){
    printf("> 构造Person...");
    this->name = "KevinChen";
    this->sex = "SuperMen";
}

void Person::say(){
    printf("我叫%s, 性别 %s, 今年%d岁. %s", this->name.c_str(), this->sex.c_str(), this->age, "\n");
}