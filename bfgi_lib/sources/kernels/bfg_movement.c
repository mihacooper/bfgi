#include "bfg_internal.h"

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
    return BFG_EXE_DONE;
}

static bfg_char finish_char_cmds[] = {'@'};
bfg_kernel_desc_t finish_desc =
{
    finish_char_cmds,
    dimof(finish_char_cmds),
    cmdFinish, NULL, NULL,
    0
};

static bfg_status cmdLeftOrRight(bfg_context context, void* mem, bfg_size size)
{
    bfg_int num;
    bfg_data_t data = {BFG_DATA_SIMPLE, &num, sizeof(num)};
    bfg_status status = bfgPopStack((bfg_stack)&((bfg_context_t*)context)->stack, &data);
    ((bfg_context_t*)context)->processor.shift.y = 0;
    if(num == 0)
        ((bfg_context_t*)context)->processor.shift.x = 1;
    else
        ((bfg_context_t*)context)->processor.shift.x = -1;
    return status;
}

static bfg_char left_or_right_cmds[] = {'_'};
bfg_kernel_desc_t left_or_right_desc =
{
    left_or_right_cmds,
    dimof(left_or_right_cmds),
    cmdLeftOrRight, NULL, NULL,
    0
};

static bfg_status cmdUpOrDown(bfg_context context, void* mem, bfg_size size)
{
    bfg_int num;
    bfg_data_t data = {BFG_DATA_SIMPLE, &num, sizeof(num)};
    bfg_status status = bfgPopStack((bfg_stack)&((bfg_context_t*)context)->stack, &data);
    ((bfg_context_t*)context)->processor.shift.x = 0;
    if(num == 0)
        ((bfg_context_t*)context)->processor.shift.y = 1;
    else
        ((bfg_context_t*)context)->processor.shift.y = -1;
    return status;
}

static bfg_char up_or_down_cmds[] = {'|'};
bfg_kernel_desc_t up_or_down_desc =
{
    up_or_down_cmds,
    dimof(up_or_down_cmds),
    cmdUpOrDown, NULL, NULL,
    0
};

static bfg_status cmdRandomMove(bfg_context context, void* mem, bfg_size size)
{
    srand((unsigned)time(NULL));
    bfg_int dir = rand() % 4;
    switch (dir) {
    case 0:
        ((bfg_context_t*)context)->processor.shift.x = 0;
        ((bfg_context_t*)context)->processor.shift.y = -1;
        break;
    case 1:
        ((bfg_context_t*)context)->processor.shift.x = 1;
        ((bfg_context_t*)context)->processor.shift.y = 0;
        break;
    case 2:
        ((bfg_context_t*)context)->processor.shift.x = 0;
        ((bfg_context_t*)context)->processor.shift.y = 1;
        break;
    case 3:
        ((bfg_context_t*)context)->processor.shift.x = -1;
        ((bfg_context_t*)context)->processor.shift.y = 0;
        break;
    default:
        break;
    }
    return BFG_SUCCESS;
}

static bfg_char random_move_cmds[] = {'?'};
bfg_kernel_desc_t random_move_desc =
{
    random_move_cmds,
    dimof(random_move_cmds),
    cmdRandomMove, NULL, NULL,
    0
};

static bfg_status cmdJump(bfg_context context, void* mem, bfg_size size)
{
    ((bfg_context_t*)context)->processor.pos.x += ((bfg_context_t*)context)->processor.shift.x;
    ((bfg_context_t*)context)->processor.pos.y += ((bfg_context_t*)context)->processor.shift.y;
    return BFG_SUCCESS;
}

static bfg_char jump_cmds[] = {'#'};
bfg_kernel_desc_t jump_desc =
{
    jump_cmds,
    dimof(jump_cmds),
    cmdJump, NULL, NULL,
    0
};

