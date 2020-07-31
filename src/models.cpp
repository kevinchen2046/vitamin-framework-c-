#include "core/vitamin.h"
#include "core/logger.h"
#include "models.h"

void Models::initialize(){
    
    Vitamin *ins=Vitamin::instance();
    ins->initialize();
    ins->__register<ModelUser>();
    ins->__register<ModelLogin>();
    ins->initializeInjects();
}