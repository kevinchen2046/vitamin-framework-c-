#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <limits>
#include <map>

#include "core/helper.hpp"
#include "core/logger.h"
#include "models.h"

using namespace std;
using namespace vitamin;

int main()
{
    //支持UTF8，防止中文乱码
    system("chcp 65001");

    Vitamin::instance().__register<ModelUser>();
    Vitamin::instance().__register<ModelLogin>();
    Vitamin::instance().__register<ChatCmd>();
    Vitamin::instance().initializeInjects();
    Vitamin::instance().emitter->emit("TEST1", 45);

    ViewLogin view;
    view.enter();
    //Animal animal;
    // animal.eat();

    //delete cat;
    // Logger::log("%p,%p",cat,baseCat);
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

    //Helper::logTypes();

    system("pause");
    return 0;
}