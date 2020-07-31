#ifndef VITAMIN
#define VITAMIN

#include <iostream>
#include "helper.h"
#include "logger.h"
using namespace std;

// #define INJECT(_Access, _Field_Ty, _Field_Key, _Obj_Ty)      \
//     _Access:                                                 \
//     _Field_Ty _Field_Key;                                    \
//                                                              \
// private:                                                     \
//     class __field_register_##_Field_Key##__                  \
//     {                                                        \
//     public:                                                  \
//         __field_register_##_Field_Key##__()                  \
//         {                                                    \
//             static tat::__field_register__ reg_##_Field_Key( \
//                 _Obj_Ty::get_class_ptr(),                    \
//                 _OFFSET_(_Obj_Ty, _Field_Key),               \
//                 #_Field_Key);                                \
//         }                                                    \
//     } _Field_Key##_register;

// template <typename VAL>
// ModelBase Inject(VAL clazz){
//     return NULL;
// }

template <typename T>
bool isModel(T val);

template <typename T>
bool isView(T val);

template <typename T>
bool isCommand(T val);

class ModelBase
{
public:
    ModelBase();
    ~ModelBase();
    virtual void initialize();
    virtual void reset();
};

class ViewBase
{
public:
    ViewBase();
    ~ViewBase();

    virtual void enter();
    virtual void exit();

protected:
    virtual void addChildren();
};

class CommandBase
{
public:
    CommandBase();
    ~CommandBase();
    virtual void exec();
};

class Vitamin
{
private:
    Injector<ModelBase> *__injector1;
    Injector<CommandBase> *__injector2;

public:
    Vitamin()
    {
        this->initialize();
    }
    static Vitamin *instance();
    void initialize()
    {
        this->__injector1 = new Injector<ModelBase>;
        this->__injector2 = new Injector<CommandBase>;
    }

    template <typename C>
    void __register()
    {
        bool result = this->__injector1->___register<C>();
        if (!result)
            this->__injector2->___register<C>();
        //Logger::info("Register:%s", Helper::getDefineName<C>().c_str());
    }

    void initializeInjects()
    {
        this->__injector1->log();
        this->__injector2->log();
        this->__injector1->forEach([](ModelBase* model){
            model->initialize();
        });
    }

    template <typename C>
    C* inject()
    {
        C* inst = this->__injector1->inject<C*>();
        if (&inst == NULL)
        {
            inst = this->__injector2->inject<C*>();
        }
        Logger::info("Inject:%s,Instance:%p", Helper::getDefineName<C>().c_str(), inst);
        return inst;
    }
};
#endif