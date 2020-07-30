
#include <iostream>
#include <map>
#include <typeinfo>
#include <cxxabi.h>
#include <string>

#include "vitamin.h"
#include "logger.h"

using namespace std;

string bool_to_str(int value)
{
    return value > 0 ? "true" : "false";
}

string getRealClassName(const char *name)
{
    int status;
    char *real_name;
    real_name = abi::__cxa_demangle(name, nullptr, nullptr, &status);
    string s(real_name);
    free(real_name);
    real_name = nullptr;
    return s;
}

template <typename T>
string getDefineName()
{
    return getRealClassName(typeid(T).name());
}

template <typename VAL>
string getDefineName(VAL val)
{
    return getRealClassName(typeid(val).name());
}

ModelBase::ModelBase(){
    Injector::__register(this);
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
    Injector::__register(this);
}
CommandBase::~CommandBase()
{
}
void CommandBase::exec()
{
}

template <typename T>
bool isModel(T val){
    try{
        ModelBase *base = dynamic_cast<ModelBase*>(val);
        return base!=0;
    }catch(char *str){
        return false;
    }
}

template <typename T>
bool isView(T val){
    try{
        ViewBase *base = dynamic_cast<ViewBase*>(val);
        return base!=0;
    }catch(char *str){
        return false;
    }
}

template <typename T>
bool isCommand(T val){
    try{
        CommandBase *base = dynamic_cast<CommandBase*>(val);
        return base!=0;
    }catch(char *str){
        return false;
    }
}


template <typename T>
void Injector::__register(T val)
{
    // const char *className = getDefineName(val).c_str();
    // if (isModel(val))
    // {
    //     Logger::log("%s %p", className, val);
    //     __modelmap__[className]=dynamic_cast<ModelBase*>(val);
    //     //Injector::__modelmap__.insert(make_pair(className, val));
    // }
    // else if (isCommand(val))
    // {
    //     Logger::log("%s %p", className, val);
    //     __cmdmap__[className]=dynamic_cast<CommandBase*>(val);
    //     //Injector::__cmdmap__[className]=val;
    //     //Injector::__cmdmap__[className] = val;
    // }
}
