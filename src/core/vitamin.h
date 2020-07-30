#ifndef VITAMIN
#define VITAMIN

#include <iostream>
#include "inject.h"
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
    Injector<ModelBase*>* __modelInjector;
    Injector<CommandBase*>* __cmdInjector;
public:
    Vitamin();
    static Vitamin* instance();

    void initialize();

    template <typename T>
    void inject();
};

#endif