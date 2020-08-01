#include "event.hpp"
using namespace vitamin;
namespace vitamin
{
    /*
     *  Ctor & Dtor
     */

    EventEmitter::EventEmitter() {}

    EventEmitter::EventEmitter(const EventEmitter &ee) : _listeners(ee._listeners) {}

    EventEmitter &EventEmitter::operator=(const EventEmitter &ee)
    {
        if (this == &ee)
            return (*this);
        _listeners = ee._listeners;
        return (*this);
    }

    EventEmitter::~EventEmitter() {}

    /*
     *  Public member functions
     */

    EventEmitter &EventEmitter::addListener(std::string event_id, std::function<void()> cb)
    {
        _listeners.insert(std::make_pair(event_id, std::make_shared<Listener<>>(event_id, cb)));
        return (*this);
    }

    EventEmitter &EventEmitter::on(std::string event_id, std::function<void()> cb)
    {
        return (this->addListener(event_id, cb));
    }

    EventEmitter &EventEmitter::removeListener(std::string listener_id)
    {
        auto i = std::find_if(_listeners.begin(), _listeners.end(), [&](std::pair<const std::string, std::shared_ptr<ListenerBase>> p) { return (p.second->id == listener_id); });
        if (i != _listeners.end())
            _listeners.erase(i);
        else
            throw std::invalid_argument("EventEmitter::remove_listener: Invalid listener id.");
        return (*this);
    }
} // namespace vitamin