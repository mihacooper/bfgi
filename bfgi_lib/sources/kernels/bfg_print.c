#include "bfg_internal.h"

static bfg_status cmdPrintNumber(bfg_context context, void* mem, bfg_size size)
{
    bfg_int number;
    bfg_data_t data = {BFG_DATA_SIMPLE, &number, sizeof(number)};
    bfg_status status = bfgPopStack((bfg_stack)&((bfg_context_t*)context)->stack, &data);
    if(status != BFG_SUCCESS)
    {
        return status;
    }
    else
    {
        printf("%d", *((bfg_int*)data.mem));
    }
    return BFG_SUCCESS;
}

static bfg_char print_num_char_cmds[] = {'.'};
bfg_kernel_desc_t print_num_desc =
{
    print_num_char_cmds,
    dimof(print_num_char_cmds),
    cmdPrintNumber, NULL, NULL,
    0
};

static bfg_status cmdPrintChar(bfg_context context, void* mem, bfg_size size)
{
    bfg_int number;
    bfg_data_t data = {BFG_DATA_SIMPLE, &number, sizeof(number)};
    bfg_status status = bfgPopStack((bfg_stack)&((bfg_context_t*)context)->stack, &data);
    if(status != BFG_SUCCESS)
    {
        return status;
    }
    else
    {
        bfg_int integer = *((bfg_int*)data.mem);
        if(integer > 255 || integer < 0)
        {
            return BFG_PRINT_CHAR_ERROR;
        }
        bfg_char character = integer;
        printf("%c", character);
    }
    return BFG_SUCCESS;
}

static bfg_char print_char_char_cmds[] = {','};
bfg_kernel_desc_t print_char_desc =
{
    print_char_char_cmds,
    dimof(print_char_char_cmds),
    cmdPrintChar, NULL, NULL,
    0
};

