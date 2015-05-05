#include "bfg_internal.h"

typedef bfg_int (*bfg_arith_f)(bfg_int, bfg_int);
static bfg_status cmdArithmetic(bfg_context context, void* mem, bfg_size size, bfg_arith_f func)
{
    bfg_int number_1, number_2, res;
    bfg_data_t data_1 = {BFG_DATA_SIMPLE, &number_1, sizeof(number_1)};
    bfg_data_t data_2 = {BFG_DATA_SIMPLE, &number_2, sizeof(number_2)};
    bfg_data_t data_res = {BFG_DATA_SIMPLE, &res, sizeof(res)};
    bfg_status status = BFG_SUCCESS;
    status |= bfgPopStack((bfg_stack)&((bfg_context_t*)context)->stack, &data_1);
    status |= bfgPopStack((bfg_stack)&((bfg_context_t*)context)->stack, &data_2);
    if(status == BFG_SUCCESS)
    {
        res = func(number_1, number_2);
        status = bfgPushStack((bfg_stack)&((bfg_context_t*)context)->stack, &data_res);
    }
    return status;
}

#define KERNEL_FUNC(name, op) \
  static bfg_int f_##name(bfg_int left, bfg_int right){ return (bfg_int)(left op right); }

#define KERNEL_CMD(name) \
    static bfg_status cmd_##name(bfg_context context, void* mem, bfg_size size) { return cmdArithmetic(context, mem, size, f_##name); }

#define KERNEL_DESC(name, sop) \
    static bfg_char name##_cmds[] = {sop};\
    bfg_kernel_desc_t name##_desc =\
    {\
        name##_cmds,\
        dimof(name##_cmds),\
        cmd_##name, NULL, NULL, 0\
    };

#define GENERATE_KERNEL(name, op, sop) \
    KERNEL_FUNC(name, op) \
    KERNEL_CMD(name) \
    KERNEL_DESC(name, sop) \

GENERATE_KERNEL(add, +, '+')
GENERATE_KERNEL(sub, -, '-')
GENERATE_KERNEL(mul, *, '*')
GENERATE_KERNEL(div, /, '/')
GENERATE_KERNEL(mod, %, '%')
GENERATE_KERNEL(lt,  <, '`')

static bfg_status cmdLogicalNot(bfg_context context, void* mem, bfg_size size)
{
    bfg_int input, res;
    bfg_data_t data_in = {BFG_DATA_SIMPLE, &input, sizeof(input)};
    bfg_data_t data_res = {BFG_DATA_SIMPLE, &res, sizeof(res)};
    bfg_status status = BFG_SUCCESS;
    status |= bfgPopStack((bfg_stack)&((bfg_context_t*)context)->stack, &data_in);
    if(status == BFG_SUCCESS)
    {
        res = (bfg_int)(!input);
        status = bfgPushStack((bfg_stack)&((bfg_context_t*)context)->stack, &data_res);
    }
    return status;
}

static bfg_char not_cmds[] = {'!'};
bfg_kernel_desc_t not_desc =
{
    not_cmds,
    dimof(not_cmds),
    cmdLogicalNot, NULL, NULL, 0
};

