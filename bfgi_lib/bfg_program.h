#ifndef BFG_PROGRAM_H
#define BFG_PROGRAM_H

#include "bfg_api.h"

bfg_status bfgLoadProgramCode(bfg_context context, bfg_char** code, bfg_size cols, bfg_size rows, bfg_mem_type mem);
bfg_status bfgExecuteProgram(bfg_context context);

#endif // BFG_PROGRAM_H
