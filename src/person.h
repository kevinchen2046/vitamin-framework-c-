#ifndef PERSON
#define PERSON

#include <iostream>
#include <stdio.h>
#include "core/logger.h"
using namespace std;

enum Color
{
    red,
    green,
    blue
};
struct Point
{
    int x;
    int y;
};

class Animal
{
public:
    Animal()
    {
        Logger::log("Animal Create!");
    }
    virtual ~Animal()
    {
        Logger::log("Animal Delete!");
    }
    virtual void eat()
    {
        Logger::log("this is Animal");
    }
};
class Cat : public Animal
{
public:
    Cat()
    {
        Logger::log("Cat Create!");
    }
    virtual ~Cat()
    {
        Logger::log("Cat Delete!");
    }
    void eat()
    {
        Logger::log("this is Cat");
    }
};

class Person{
    public:
        int age;
        string name;
        string sex;

    public:
        //构造函数
        Person();
        void say();
};
#endif