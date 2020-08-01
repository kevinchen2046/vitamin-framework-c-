#ifndef EMITIUM_EVENTEMITTER_HPP
#define EMITIUM_EVENTEMITTER_HPP

#include <string>
#include <functional>
#include <map>
#include <memory>
#include <list>
#include <algorithm>

using namespace std;
namespace vitamin
{
    class EventEmitter
    {
    public:
        EventEmitter();
        EventEmitter(const EventEmitter &);
        EventEmitter &operator=(const EventEmitter &);
        ~EventEmitter();

        template <typename... Args>
        EventEmitter &addListener(std::string, std::function<void(Args...)>);
        EventEmitter &addListener(std::string, std::function<void()>);

        template <typename LambdaType>
        EventEmitter &addListener(std::string event_id, LambdaType lambda)
        {
            return (addListener(event_id, make_function(lambda)));
        }

        EventEmitter &removeListener(std::string);

        template <typename... Args>
        EventEmitter &on(std::string, std::function<void(Args...)>);
        EventEmitter &on(std::string, std::function<void()>);

        template <typename LambdaType>
        EventEmitter &on(std::string event_id, LambdaType lambda)
        {
            return on(event_id, make_function(lambda));
        }

        template <typename... Args>
        EventEmitter &emit(std::string, Args...);

    private:
        struct ListenerBase
        {
            ListenerBase() {}
            ListenerBase(std::string i) : id(i) {}
            virtual ~ListenerBase() {}

            std::string id;
        };

        template <typename... Args>
        struct Listener : public ListenerBase
        {
            Listener() {}
            Listener(std::string i, std::function<void(Args...)> c) : ListenerBase(i), cb(c) {}

            std::function<void(Args...)> cb;
        };

        template <typename T>
        struct function_traits : public function_traits<decltype(&T::operator())>
        {
        };

        template <typename ClassType, typename ReturnType, typename... Args>
        struct function_traits<ReturnType (ClassType::*)(Args...) const>
        {
            typedef std::function<ReturnType(Args...)> f_type;
        };

        template <typename L>
        typename function_traits<L>::f_type make_function(L l)
        {
            return ((typename function_traits<L>::f_type)(l));
        }

        std::multimap<std::string, std::shared_ptr<ListenerBase>> _listeners;
    };

    template <typename... Args>
    EventEmitter &EventEmitter::addListener(std::string event_id, std::function<void(Args...)> cb)
    {
        //printf("<<<<<<<<<<<<<<%s",event_id.c_str());
        _listeners.insert(std::make_pair(event_id, std::make_shared<Listener<Args...>>(event_id, cb)));
        return (*this);
    }

    template <typename... Args>
    EventEmitter &EventEmitter::on(std::string event_id, std::function<void(Args...)> cb)
    {
        return (this->addListener(event_id, cb));
    }

    template <typename... Args>
    EventEmitter &EventEmitter::emit(std::string event_id, Args... args)
    {
        
        std::list<std::shared_ptr<Listener<Args...>>> handlers;
        {
            auto range = _listeners.equal_range(event_id);
            handlers.resize(std::distance(range.first, range.second));
            //printf(">>>>>>>>>>>>>>>>>>>%d",handlers.size());
            std::transform(range.first, range.second, handlers.begin(), [](std::pair<const std::string, std::shared_ptr<ListenerBase>> p) {
                auto l = std::dynamic_pointer_cast<Listener<Args...>>(p.second);
                if (l)
                    return (l);
                else
                    throw std::logic_error("EventEmitter::Emit: Invalid event signature.");
            });
        }
        for (auto &h : handlers)
            h->cb(args...);
        return (*this);
    }
} // namespace vitamin

#endif //EMITIUM_EVENTEMITTER_HPP