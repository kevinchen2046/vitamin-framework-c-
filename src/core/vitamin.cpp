
#include <iostream>
#include <map>
#include <string>

#include "helper.h"
#include "logger.h"
#include "vitamin.h"

using namespace std;

ModelBase::ModelBase()
{
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
}
CommandBase::~CommandBase()
{
}
void CommandBase::exec()
{
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
