#include "core/vitamin.h"
#include "core/logger.h"
#include "models.h"

void Models::initialize(){
    Vitamin *ins=Vitamin::instance();
    ins->inject<ModelUser>();
    ins->inject<ModelLogin>();
}