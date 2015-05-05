#ifndef BFG_PARSER_H
#define BFG_PARSER_H

#ifdef __cplusplus
extern "C"{
#endif

bfg_status  bfgInitParser(bfg_context context);
bfg_kernel  bfgQueryKernelData(bfg_context context, bfg_char ch_cmd);
bfg_status  bfgReleaseParser(bfg_context context);

#ifdef __cplusplus
}
#endif

#endif // BFG_PARSER_H
