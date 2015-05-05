#ifndef BFG_PROGRAM_H
#define BFG_PROGRAM_H

#ifdef __cplusplus
extern "C"{
#endif

bfg_status bfgLoadProgramCode(bfg_context context, bfg_char** code, bfg_size cols, bfg_size rows, bfg_mem_type mem);
bfg_status bfgExecuteProgram(bfg_context context);

#ifdef __cplusplus
}
#endif

#endif // BFG_PROGRAM_H
