#include "core/vitamin.hpp"
#include "core/logger.h"
#include "models.h"
using namespace vitamin;

//------------------------------------------------------------
//------------------------------------------------------------
ModelUser::ModelUser()
{
    this->name = "My Name is Model User!";
}
void ModelUser::initialize()
{
    this->on("TEST1", [this](int nb) {
        Logger::info("Test1 Event:%d", nb);
        this->emit("TEST2", 100);
    });
}
//------------------------------------------------------------
//------------------------------------------------------------
void ModelLogin::initialize()
{
    this->user = Vitamin::instance().inject<ModelUser>();
    Logger::info("User: %s", this->user->name.c_str());

    this->on("TEST2", [](int nb) {
        Logger::info("Test2 Event:%d", nb);
    });
}
//------------------------------------------------------------
//------------------------------------------------------------
void ChatCmd::exec()
{
    Logger::info("ChatCmd:");
}
//------------------------------------------------------------
//------------------------------------------------------------
void ViewLogin::initialize()
{
    this->login = Vitamin::instance().inject<ModelLogin>();
}
void ViewLogin::enter()
{
    Logger::info(Helper::getDefineName(this->login).c_str());
    this->exec<ChatCmd>();
}
void ViewLogin::exit()
{
}