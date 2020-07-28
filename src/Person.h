#ifndef PERSON
#define PERSON
#include <stdio.h>

using namespace std;

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