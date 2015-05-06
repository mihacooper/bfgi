#include "bfg_internal.h"

bfg_status bfgLoadProgramCode(bfg_context context, bfg_char** code, bfg_size cols, bfg_size rows, bfg_mem_type mem)
{
    BFG_CHECK_NULL(context);

    int i;
    if(mem == BFG_COPY)
    {
        ((bfg_context_t*)context)->program.code = (bfg_char**)malloc(sizeof(bfg_char*) * rows);
        for(i = 0; i < rows; i++)
        {
            ((bfg_context_t*)context)->program.code[i] = (bfg_char*)malloc(sizeof(bfg_char) * cols);
            memcpy(((bfg_context_t*)context)->program.code[i], code[i], sizeof(bfg_char) * cols);
        }
    }
    else
    {
        ((bfg_context_t*)context)->program.code = code;
    }
    ((bfg_context_t*)context)->program.cols = cols;
    ((bfg_context_t*)context)->program.rows = rows;
    return BFG_SUCCESS;
}

bfg_status bfgExecuteProgram(bfg_context context)
{
    BFG_CHECK_NULL(context);
    BFG_CHECK_NULL(((bfg_context_t*)context)->program.code);

    bfg_char**      code    = ((bfg_context_t*)context)->program.code;
    bfg_status*     status = &((bfg_context_t*)context)->processor.status;
    bfg_point_t*    pos     = &((bfg_context_t*)context)->processor.pos;
    bfg_point_t*    shift   = &((bfg_context_t*)context)->processor.shift;
    bfg_size        cols    = ((bfg_context_t*)context)->program.cols;
    bfg_size        rows    = ((bfg_context_t*)context)->program.rows;

    pos->x = 0; pos->y = -1;
    shift->x = 0; shift->y = 1;

    do
    {
        pos->x += shift->x;
        pos->y += shift->y;
        if(pos->x < 0 || pos->x >= cols || pos->y < 0 || pos->y >= rows)
        {
            *status = BFG_LEAVE_FIELD;
            break;
        }
        bfg_char ch_cmd = code[pos->y][pos->x];
        bfg_parse_func_t parser = ((bfg_context_t*)context)->parser.parse_func;
        if(parser == NULL)
        {
            BFG_PRINT("Parser isn't defined!\n");
            *status = BFG_FAILURE;
            break;
        }
        bfg_kernel_t* cmd = (bfg_kernel_t*)parser(context, ch_cmd);
        if(cmd->func == NULL)
        {
            BFG_PRINT("Unsupported command \'%c\'\n", ch_cmd);
            *status = BFG_UNSUPPORTED_CMD;
            break;
        }
        *status = cmd->func(context, cmd->mem, cmd->data_size);
    }while(*status == BFG_SUCCESS);

    return *status;
}
