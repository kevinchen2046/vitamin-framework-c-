#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <limits>
#include <map>

#include "core/vitamin.h"
#include "core/helper.h"
#include "core/logger.h"
#include "models.h"
#include "person.h"


using namespace std;

#define STR(x) #x
#define CONS(a, b) (a##e##b)


int main()
{
    //支持UTF8，防止中文乱码
    system("chcp 65001");

    Models::initialize();
    //Animal animal;
    // animal.eat();

    // Cat baseCat;
    Cat *cat = new Cat;
    cat->eat();
    Logger::log(STR(cat));         //输出字符串helloworld
    Logger::log("%f", CONS(2, 3)); //输出 2000.0
    Point p;
    p.x = 12;
    p.y = 13;
    Logger::log("%d %d", p.x, p.y);
    //delete cat;
    // Logger::log("%p,%p",cat,baseCat);
    ModelBase *model = new ModelBase;
    // Logger::info(typeid(Cat).name());
    // Logger::info(typeid(cat).name());
    // Logger::info(typeid(*cat).name());
    // Animal *animal=cat;
    // Logger::info(typeid(Animal).name());
    // Logger::info(typeid(animal).name());
    // Logger::info(typeid(*animal).name());
    // ModelBase *model=new ModelBase;
    // ModelUser *modelUser=new ModelUser;
    // Logger::info(isModel(model)?"true":"false");
    // Logger::info(isModel(cat)?"true":"false");
    // Logger::info(isModel(modelUser)?"true":"false");
    map<const char *, Cat *> *_map = new map<const char *, Cat *>;
    pair<const char *, Cat *> valueModel("bb", cat);
    _map->insert(valueModel);
    Logger::info("%p", _map->find("bb"));

    ModelLogin *login = new ModelLogin;
    login->initialize();
    return 0;
    Helper::logTypes();

    string str = "Hello";
    string megestr = str + "World!";
    Logger::info("> merge: %s , enum:%d", megestr.c_str(), Color::blue);
    Logger::log("> str: %s , length:%d", str.c_str(), str.length());

    Person person;
    person.age = 20;
    person.name = "Kevin Chen";
    person.sex = "Men";
    person.say();

    string value = "abc";
    int MAX = 3;
    int var[MAX] = {10, 100, 200};

    //将value的内存地址赋给指针p1
    string *p1 = &value;
    //将指针p1赋给指针p2
    string *p2 = p1;
    //将指针p2的内存地址赋给指针p3
    string **p3 = &p2;

    Logger::info("-------------------NULL 指针--------------------");
    string *p_null = NULL;
    Logger::log("Null 指针 *p_null 的值是:%p", p_null);

    Logger::info("-----------------指针的算术运算(递增)------------------");
    int *array_p;
    array_p = var; // 指针中的数组地址
    for (int i = 0; i < MAX; i++)
    {
        Logger::log("var[%d]的地址是:%x,值是:%d", i, array_p, *array_p);
        // 移动到下一个位置
        array_p++;
    }
    Logger::info("-----------------指针的算术运算(比较)------------------");
    array_p = var; // 指针中第一个元素的地址
    int i = 0;
    while (array_p <= &var[MAX - 1])
    {
        Logger::log("var[%d]的地址是:%x,值是:%d", i, array_p, *array_p);
        // 指向上一个位置
        array_p++;
        i++;
    }

    Logger::info("-------------------指针&数组--------------------");
    *(var + 2) = 500; //把 var[2] 赋值为 500：
    for (int i = 0; i < MAX; i++)
    {
        Logger::log("赋值前,i:%d,var值是:%x,%d,%d", i, var, *var, var[i]);
        *var = i; // 这是正确的语法
        Logger::log("赋值后,i:%d,var值是:%x,%d,%d", i, var, *var, var[i]);
        //var++;    // 这是不正确的
    }
    //把指针运算符 * 应用到 var 上是完全可以的，但修改 var 的值是非法的。这是因为 var 是一个指向数组开头的常量，不能作为左值。
    //由于一个数组名对应一个指针常量，只要不改变数组的值，仍然可以用指针形式的表达式。

    system("pause");
    return 0;
}