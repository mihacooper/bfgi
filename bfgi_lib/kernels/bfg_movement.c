#include "bfg_parser.h"

static bfg_status cmdMoveUp(bfg_context context, void* data, bfg_size size)
{
    ((bfg_context_t*)context)->processor.shift.x = 0;
    ((bfg_context_t*)context)->processor.shift.y = -1;
    return BFG_SUCCESS;
}

static bfg_char move_up_char_cmds[] = {'^'};
bfg_kernel_desc_t move_up_desc =
{
    move_up_char_cmds,
    dimof(move_up_char_cmds),
    cmdMoveUp, NULL, NULL,
    0
};

bfg_status cmdMoveDown(bfg_context context, void* data, bfg_size size)
{
    ((bfg_context_t*)context)->processor.shift.x = 0;
    ((bfg_context_t*)context)->processor.shift.y = 1;
    return BFG_SUCCESS;
}

static bfg_char move_down_char_cmds[] = {'v'};
bfg_kernel_desc_t move_down_desc =
{
    move_down_char_cmds,
    dimof(move_down_char_cmds),
    cmdMoveDown, NULL, NULL,
    0
};

static bfg_status cmdMoveRight(bfg_context context, void* data, bfg_size size)
{
    ((bfg_context_t*)context)->processor.shift.y = 0;
    ((bfg_context_t*)context)->processor.shift.x = 1;
    return BFG_SUCCESS;
}

static bfg_char move_right_char_cmds[] = {'>'};
bfg_kernel_desc_t move_right_desc =
{
    move_right_char_cmds,
    dimof(move_right_char_cmds),
    cmdMoveRight, NULL, NULL,
    0
};

static bfg_status cmdMoveLeft(bfg_context context, void* data, bfg_size size)
{
    ((bfg_context_t*)context)->processor.shift.y = 0;
    ((bfg_context_t*)context)->processor.shift.x = -1;
    return BFG_SUCCESS;
}

static bfg_char move_left_char_cmds[] = {'<'};
bfg_kernel_desc_t move_left_desc =
{
    move_left_char_cmds,
    dimof(move_left_char_cmds),
    cmdMoveLeft, NULL, NULL,
    0
};

static bfg_status cmdEmpty(bfg_context context, void* data, bfg_size size)
{
    (void)context;
    return BFG_SUCCESS;
}

static bfg_char empty_char_cmds[] = {' '};
bfg_kernel_desc_t empty_desc =
{
    empty_char_cmds,
    dimof(empty_char_cmds),
    cmdEmpty, NULL, NULL,
    0
};

static bfg_status cmdFinish(bfg_context context, void* data, bfg_size size)
{
    ((bfg_context_t*)context)->processor.status = BFG_EXE_DONE;
    return BFG_SUCCESS;
}

static bfg_char finish_char_cmds[] = {'@'};
bfg_kernel_desc_t finish_desc =
{
    finish_char_cmds,
    dimof(finish_char_cmds),
    cmdFinish, NULL, NULL,
    0
};

