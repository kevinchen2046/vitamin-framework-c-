#ifndef GAME_MODELS
#define GAME_MODELS

#include "core/vitamin.h"
#include "core/logger.h"

class Models 
{
public:
    static void initialize();
};

class ModelUser : public ModelBase
{
public:
    ModelUser()
    {
        Logger::log("ModelUser Create!");
    }
    ~ModelUser()
    {
        Logger::log("ModelUser Delete!");
    }
};

class ModelLogin : public ModelBase
{
private:
    ModelUser *user;

public:
    ModelLogin()
    {
        Logger::log("ModelLogin Create!");
    }
    ~ModelLogin()
    {
        Logger::log("ModelLogin Delete!");
    }
    void initialize(){
        Logger::info("this is user: $p",this->user);
    }
};

#endif