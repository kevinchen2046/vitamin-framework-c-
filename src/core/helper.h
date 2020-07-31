#ifndef VITAMIN_HELP
#define VITAMIN_HELP

#include <iostream>
#include <typeinfo>
#include <map>

#include "cxxabi.h"
#include "logger.h"

using namespace std;

#define STR(x) #x
#define CONS(a, b) (a##e##b)

class Helper
{
public:
    Helper();
    static void logTypes();
    static string bool_to_str(int value)
    {
        return value > 0 ? "true" : "false";
    }

    template <typename U,typename T>
    static bool isType(T val)
    {
        // string baseName=getDefineName<U>();
        // string targetName=getDefineName(val);
        try
        {
            U* base = dynamic_cast<U*>(val);
            return base != 0;
        }
        catch (char *str)
        {
            return false;
        }
    }

    static string getRealClassName(const char *name)
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
    static string getDefineName()
    {
        return getRealClassName(typeid(T).name());
    }

    template <typename T>
    static string getDefineName(T val)
    {
        return getRealClassName(typeid(val).name());
    }
};

///////////////////////////////////////

/////////////////////////////////////////////////
template <class T>
class Injector
{
public:
    map<string, T *> *__map__;
   
    Injector<T>()
    {
        this->__map__ = new map<string, T *>;
    }

    template <typename U>
    bool ___register()
    {
        U *__instance = new U;
        string className = Helper::getDefineName(__instance);
        if (Helper::isType<T>(__instance))
        {
            
            T *__value = dynamic_cast<T *>(__instance);
            pair<string, T *> __element(className, __value);
            this->__map__->insert(__element);
            //Logger::log("map:%d,className:%s, class:%p",this->__map__->size(), className, __instance);
            return true;
        }
        return false;
    }

    void log()
    {
        int size=this->__map__->size();
        Logger::line((string("Inject<"+Helper::getDefineName<T>()+"> :"+to_string(size)).c_str()));
        typename map<string, T *>::iterator __iter;
        for (__iter=this->__map__->begin(); __iter!=this->__map__->end(); __iter++)
        {
            Logger::info("%s,%s",__iter->first.c_str(),typeid(__iter->second).name());
        }
        Logger::line("");
    }

    void forEach(void (*method)(T*)){
        typename map<string, T *>::iterator __iter;
        for (__iter=this->__map__->begin(); __iter!=this->__map__->end(); __iter++)
        {
            method(__iter->second);
        }
    }

    template <typename U>
    U inject()
    {
        string className = Helper::getDefineName<U>();
        typename map<string, T *>::iterator __iter;
        __iter=this->__map__->find(className);
        U result = dynamic_cast<U>(__iter->second);
        return result;
    }
};
#endif