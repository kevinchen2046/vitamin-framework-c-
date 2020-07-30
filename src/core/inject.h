#ifndef VITAMIN_INJECT
#define VITAMIN_INJECT

#include <map>
#include "base.h"

template <class T>
class Injector
{
public:
    Injector(){
        
    }
    bool (*__isType)(T val);

    std::map<const char *, T *> *__map__;

    template <class T>
    Injector()
    {
        this->__map__=new map<const char *, T *>;
    }

    template <class T>
    void ___register()
    {
        T *__instance = new T;
        const char *className = getDefineName(__instance).c_str();
        if (this->__isType(__instance))
        {
            //Logger::log("%s %p", className, __instance);
            T *__value = dynamic_cast<T *>(__instance);
            pair<const char *, T *> __element(className, __value);
            this->__map__->insert(__element);
        }
    }

    template <class T>
    T inject()
    {
        const char *className = getDefineName<T>().c_str();
        T *result = this->__map__->find(className);
        if (result != NULL)
            return result;
        return NULL;
    }
};

#endif
