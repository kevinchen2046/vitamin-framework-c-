#ifndef PERSON_H
#define PERSON_H
#include <iostream>
using namespace std;
class Person
{
public:
    int age;
    string name;
    string sex;
public:
    Person();    //构造函数
    void say();
};
#endif