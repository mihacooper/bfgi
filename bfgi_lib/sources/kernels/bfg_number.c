#include "../bfg_internal.h"

typedef struct
{
    bfg_char ch;
    bfg_int  num;
}CharToNum;

static CharToNum map_char_to_num[] =
{
    {'0', 0},
    {'1', 1},
    {'2', 2},
    {'3', 3},
    {'4', 4},
    {'5', 5},
    {'6', 6},
    {'7', 7},
    {'8', 8},
    {'9', 9},
};

static bfg_char number_char_cmds[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

typedef struct
{
    bfg_size degree;
    bfg_int  number;
}LongNumber;

static bfg_kernel SubParser(bfg_context context, bfg_char ch_cmd);

static bfg_status cmdNumber(bfg_context context, void* data, bfg_size size)
{
    bfg_point_t pos = ((bfg_context_t*)context)->processor.pos;
    bfg_char    sym = ((bfg_context_t*)context)->program.code[pos.y][pos.x];
    bfg_int     num;

    int i;
    for(i = 0; i < dimof(map_char_to_num); i++)
        if(map_char_to_num[i].ch == sym)
            num = map_char_to_num[i].num;
    
    LongNumber* str = (LongNumber*)data;
    str->number += num * (bfg_int)pow((float)10., (float)str->degree);
    str->degree++;
    ((bfg_context_t*)context)->parser.parse_func = SubParser;
    return BFG_SUCCESS;
}

static bfg_kernel SubParser(bfg_context context, bfg_char ch_cmd)
{
    bfg_kernel_t* kernel = (bfg_kernel_t*)(((bfg_context_t*)context)->parser.def_parse_func(context, ch_cmd));
    if(kernel->func != cmdNumber)
    {
        bfg_data_t data;
        bfg_kernel_t* num_kernel = (bfg_kernel_t*)bfgQueryKernelData(context, map_char_to_num[0].ch);
        LongNumber* lnum = ((LongNumber*)num_kernel->mem);
        data.type = BFG_DATA_SIMPLE;
        data.mem  = &lnum->number;
        data.data_size = sizeof(bfg_int);
        bfgPushStack(&((bfg_context_t*)context)->stack, &data);
        lnum->degree = 0;
        lnum->number = 0;
        ((bfg_context_t*)context)->parser.parse_func = ((bfg_context_t*)context)->parser.def_parse_func;
    }
    return (bfg_kernel)kernel;
}

static bfg_status MemInit(void* data, bfg_size size)
{
    LongNumber* str = (LongNumber*)data;
    str->degree = 0;
    str->number = 0;
}

bfg_kernel_desc_t number_desc =
{
    number_char_cmds,
    dimof(number_char_cmds),
    cmdNumber, MemInit, NULL,
    sizeof(LongNumber)
};
