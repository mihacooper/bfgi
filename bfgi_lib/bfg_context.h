#ifndef BFGL_CONTEXT_H
#define BFGL_CONTEXT_H

#include "bfg_api.h"

bfg_context bfgCreateContext();
bfg_status  bfgReleaseContext(bfg_context* context);

#endif // BFGL_CONTEXT_H
