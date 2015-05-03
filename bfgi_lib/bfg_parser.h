#ifndef BFG_PARSER_H
#define BFG_PARSER_H

#include "bfg_api.h"

bfg_status    bfgInitParser(bfg_context context);
bfg_kernel_t  bfgParseCommand(bfg_context context, bfg_char ch_cmd);
bfg_kernel_t* bfgQueryKernelData(bfg_context context, bfg_char ch_cmd);
bfg_status    bfgReleaseParser(bfg_context context);

#endif // BFG_PARSER_H
