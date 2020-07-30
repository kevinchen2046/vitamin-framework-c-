
#include <iostream>
#include <map>
#include <string>

#include "vitamin.h"
#include "logger.h"
#include "inject.h"

using namespace std;

ModelBase::ModelBase()
{
    //Injector::__register(this);
}

ModelBase::~ModelBase(void)
{
}
void ModelBase::initialize()
{
}
void ModelBase::reset()
{
}

ViewBase::ViewBase(void)
{
    this->addChildren();
}
ViewBase::~ViewBase(void)
{
}
void ViewBase::addChildren()
{
}
void ViewBase::enter()
{
}
void ViewBase::exit()
{
}

CommandBase::CommandBase()
{
    //Injector::__register(this);
}
CommandBase::~CommandBase()
{
}
void CommandBase::exec()
{
}

template <typename T>
bool isModel(T val)
{
    try
    {
        ModelBase *base = dynamic_cast<ModelBase *>(val);
        return base != 0;
    }
    catch (char *str)
    {
        return false;
    }
}

template <typename T>
bool isView(T val)
{
    try
    {
        ViewBase *base = dynamic_cast<ViewBase *>(val);
        return base != 0;
    }
    catch (char *str)
    {
        return false;
    }
}

template <typename T>
bool isCommand(T val)
{
    try
    {
        CommandBase *base = dynamic_cast<CommandBase *>(val);
        return base != 0;
    }
    catch (char *str)
    {
        return false;
    }
}
Vitamin *__instance;
Vitamin *Vitamin::instance()
{
    if (__instance == NULL)
    {
        __instance = new Vitamin;
    }
    return __instance;
}

Vitamin::Vitamin()
{
    this->__modelInjector = new Injector<ModelBase *>;
    this->__cmdInjector = new Injector<CommandBase *>;
}

void Vitamin::initialize()
{
    //Injector
    this->__modelInjector->__isType = isModel;
    this->__cmdInjector->__isType = isCommand;
}

template <typename T>
void Vitamin::inject()
{
    
}
