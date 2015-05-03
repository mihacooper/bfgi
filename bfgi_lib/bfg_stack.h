#ifndef BFG_STACK_H
#define BFG_STACK_H

bfg_status bfgInitStack(bfg_stack stack);
bfg_bool   bfgStackIsEmpty(bfg_stack stack);
bfg_status bfgAddStackPage(bfg_stack stack);
bfg_status bfgPushStack(bfg_stack stack, bfg_data_t* data);
bfg_status bfgPopStack(bfg_stack stack, bfg_data_t* data);
bfg_status bfgReleaseStack(bfg_stack stack);

#endif // BFG_STACK_H
