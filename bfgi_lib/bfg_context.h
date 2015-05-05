#ifndef BFGL_CONTEXT_H
#define BFGL_CONTEXT_H

#ifdef __cplusplus
extern "C"{
#endif

bfg_context bfgCreateContext();
bfg_status  bfgReleaseContext(bfg_context* context);

#ifdef __cplusplus
}
#endif

#endif // BFGL_CONTEXT_H
