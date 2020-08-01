#ifndef GAME_MODELS
#define GAME_MODELS

#include "core/vitamin.hpp"

using namespace vitamin;

class ModelUser : public ModelBase
{
public:
    string name;
    ModelUser();
    void initialize();
};

class ModelLogin : public ModelBase
{
private:
    ModelUser *user;

public:
    void initialize();
};

class ChatCmd : public CommandBase
{
public:
    void exec();
};

class ViewLogin : public ViewBase
{
private:
    ModelLogin *login;

public:
    void initialize();
    void enter();
    void exit();
};

#endif