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
    string name;
    ModelUser()
    {
        this->name="My Name is Model User!";
        
    }
    void initialize(){
       //Logger::log("ModelUser initialize!");
    }
};

class ModelLogin : public ModelBase
{
private:
    ModelUser *user;

public:
    void initialize(){
        this->user=Vitamin::instance()->inject<ModelUser>();
        Logger::info("User: %s",this->user->name.c_str());
    }
};

#endif