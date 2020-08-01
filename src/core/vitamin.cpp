
#include <iostream>
#include <map>
#include <string>
#include "helper.hpp"
#include "logger.h"
#include "vitamin.hpp"

using namespace std;
using namespace vitamin;
namespace vitamin
{
    /////////////////////////////////////////////////////////
    ModelBase::ModelBase() {}
    ModelBase::~ModelBase() {}
    void ModelBase::initialize() {}
    void ModelBase::reset() {}
    EventEmitter ModelBase::off(std::string listener_id)
    {
        return Vitamin::instance().emitter->removeListener(listener_id);
    };
    /////////////////////////////////////////////////////////
    ViewBase::ViewBase()
    {
        this->addChildren();
        this->initialize();
    }
    ViewBase::~ViewBase() {}
    void ViewBase::addChildren() {}
    void ViewBase::initialize() {}
    void ViewBase::enter() {}
    void ViewBase::exit() {}
    EventEmitter ViewBase::on(std::string event_id, std::function<void()> cb)
    {
        return Vitamin::instance().emitter->addListener(event_id, cb);
    };
    EventEmitter ViewBase::off(std::string listener_id)
    {
        return Vitamin::instance().emitter->removeListener(listener_id);
    };
    /////////////////////////////////////////////////////////
    CommandBase::CommandBase() {}
    CommandBase::~CommandBase() {}
    void CommandBase::exec() {}
    /////////////////////////////////////////////////////////
} // namespace vitamin