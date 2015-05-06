#include "bfg_internal.h"

static bfg_status cmdCopy(bfg_context context, void* mem, bfg_size size)
{
    bfg_int num;
    bfg_data_t data = {BFG_DATA_SIMPLE, &num, sizeof(num)};
    bfg_status status = BFG_SUCCESS;
    status = bfgPopStack((bfg_stack)&((bfg_context_t*)context)->stack, &data);
    if(status == BFG_SUCCESS)
    {
        status = bfgPushStack((bfg_stack)&((bfg_context_t*)context)->stack, &data);
        status = bfgPushStack((bfg_stack)&((bfg_context_t*)context)->stack, &data);
    }
    return status;
}

static bfg_char copy_cmds[] = {':'};
bfg_kernel_desc_t copy_desc =
{
    copy_cmds,
    dimof(copy_cmds),
    cmdCopy, NULL, NULL, 0
};

static bfg_status cmdSwap(bfg_context context, void* mem, bfg_size size)
{
    bfg_int num1, num2;
    bfg_data_t data1 = {BFG_DATA_SIMPLE, &num1, sizeof(num1)};
    bfg_data_t data2 = {BFG_DATA_SIMPLE, &num2, sizeof(num2)};
    bfg_status status = BFG_SUCCESS;
    status |= bfgPopStack((bfg_stack)&((bfg_context_t*)context)->stack, &data1);
    status |= bfgPopStack((bfg_stack)&((bfg_context_t*)context)->stack, &data2);
    if(status == BFG_SUCCESS)
    {
        status = bfgPushStack((bfg_stack)&((bfg_context_t*)context)->stack, &data1);
        status = bfgPushStack((bfg_stack)&((bfg_context_t*)context)->stack, &data2);
    }
    return status;
}

static bfg_char swap_cmds[] = {'\\'};
bfg_kernel_desc_t swap_desc =
{
    swap_cmds,
    dimof(swap_cmds),
    cmdSwap, NULL, NULL, 0
};

static bfg_status cmdRemove(bfg_context context, void* mem, bfg_size size)
{
    bfg_int num;
    bfg_data_t data = {BFG_DATA_SIMPLE, &num, sizeof(num)};
    bfg_status status = bfgPopStack((bfg_stack)&((bfg_context_t*)context)->stack, &data);
    return status;
}

static bfg_char remove_cmds[] = {'&'};
bfg_kernel_desc_t remove_desc =
{
    remove_cmds,
    dimof(remove_cmds),
    cmdRemove, NULL, NULL, 0
};

