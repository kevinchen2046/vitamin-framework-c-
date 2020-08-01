#ifndef VITAMIN
#define VITAMIN

#include <iostream>
#include "helper.hpp"
#include "event.hpp"
#include "logger.h"
using namespace std;
using namespace vitamin;
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

namespace vitamin
{
    class ModelBase
    {
    public:
        ModelBase();
        ~ModelBase();
        virtual void initialize();
        virtual void reset();
        template <typename LambdaType>
        EventEmitter on(std::string event_id, LambdaType lambda);
        EventEmitter on(std::string event_id, std::function<void()> cb);
        template <typename... Args>
        EventEmitter on(std::string event_id, std::function<void(Args...)> cb);
        EventEmitter off(std::string listener_id);
        template <typename... Args>
        EventEmitter emit(std::string event_id, Args... args);
        template <typename T>
        void exec();
    };

    class ViewBase
    {
    public:
        ViewBase();
        ~ViewBase();
        virtual void initialize();
        virtual void enter();
        virtual void exit();
        template <typename LambdaType>
        EventEmitter on(std::string event_id, LambdaType lambda);
        EventEmitter on(std::string event_id, std::function<void()> cb);
        template <typename... Args>
        EventEmitter on(std::string event_id, std::function<void(Args...)> cb);
        EventEmitter off(std::string listener_id);
        template <typename T>
        void exec();

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

    //////////////////////////////////////////////////////////

    class Vitamin
    {

    private:
        Injector<ModelBase> *__injector1;
        Injector<CommandBase> *__injector2;

    public:
        EventEmitter *emitter;
        Vitamin() { this->initialize(); };

        Vitamin(const Vitamin &) = delete;
        Vitamin &operator=(const Vitamin &) = delete;
        static Vitamin &instance()
        {
            static Vitamin __instance;
            return __instance;
        }
        void initialize()
        {
            this->emitter = new EventEmitter;
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
            this->__injector1->forEach([](ModelBase *model) {
                model->initialize();
            });
        }

        template <typename C>
        void exec()
        {
            C *inst = this->__injector2->inject<C *>();
            if (&inst != NULL)
                inst->exec();
            else
                Logger::error("Can't find Command:%s", Helper::getDefineName<C>().c_str());
        }

        template <typename C>
        C *inject()
        {
            C *inst = this->__injector1->inject<C *>();
            if (&inst == NULL)
            {
                inst = this->__injector2->inject<C *>();
            }
            if (&inst == NULL)
            {
                Logger::error("Can't find vitamin's instance item:%s", Helper::getDefineName<C>().c_str());
            }
            else
            {
                Logger::info("Inject:%s", Helper::getDefineName<C>().c_str());
            }
            return inst;
        }
    };

    /////////////////////////////////////////////
    template <typename LambdaType>
    EventEmitter ModelBase::on(std::string event_id, LambdaType lambda)
    {
        return Vitamin::instance().emitter->addListener(event_id, lambda);
    };
    template <typename... Args>
    EventEmitter ModelBase::on(std::string event_id, std::function<void(Args...)> cb)
    {
        return Vitamin::instance().emitter->addListener(event_id, cb);
    };
    template <typename... Args>
    EventEmitter ModelBase::emit(std::string event_id, Args... args)
    {
        return Vitamin::instance().emitter->emit(event_id, args...);
    };
    template <typename T>
    void ModelBase::exec()
    {
        Vitamin::instance().exec<T>();
    }
    template <typename LambdaType>
    EventEmitter ViewBase::on(std::string event_id, LambdaType lambda)
    {
        return Vitamin::instance().emitter->on(event_id, lambda);
    };

    template <typename... Args>
    EventEmitter ViewBase::on(std::string event_id, std::function<void(Args...)> cb)
    {
        return Vitamin::instance().emitter->addListener(event_id, cb);
    };
    template <typename T>
    void ViewBase::exec()
    {
        Vitamin::instance().exec<T>();
    }
}; // namespace vitamin
#endif