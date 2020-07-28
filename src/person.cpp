#include <iostream>
#include "person.h"
#include "core/logger.h"
Person::Person(){
    Logger::log("> 构造Person...");
    this->name = "KevinChen";
    this->sex = "SuperMen";
}

void Person::say(){
    Logger::debug("我叫%s, 性别 %s, 今年%d岁.", this->name.c_str(), this->sex.c_str(), this->age);
}