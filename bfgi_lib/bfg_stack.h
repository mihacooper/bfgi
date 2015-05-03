#ifndef BFG_STACK_H
#define BFG_STACK_H

#include "bfg_api.h"

bfg_status bfgInitStack(bfg_stack_t* stack);
bfg_bool   bfgStackIsEmpty(bfg_stack_t* stack);
bfg_status bfgAddStackPage(bfg_stack_t* stack);
bfg_status bfgPushStack(bfg_stack_t* stack, bfg_data_t* data);
bfg_status bfgPopStack(bfg_stack_t* stack, bfg_data_t* data);
bfg_status bfgReleaseStack(bfg_stack_t* stack);

#endif // BFG_STACK_H
