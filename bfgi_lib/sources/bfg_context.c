#include "bfg_internal.h"

bfg_context bfgCreateContext()
{
    bfg_status status;
    bfg_context_t* context = (bfg_context_t*)malloc(sizeof(bfg_context_t));
    if( context == NULL)
    {
        BFG_PRINT("Memory allocation failure!\n");
        return NULL;
    }
    status = bfgInitStack((bfg_stack)&context->stack);
    if( status != BFG_SUCCESS)
    {
        free(context);
        BFG_PRINT("Stack initialization failure!\n");
        return NULL;
    }
    memset(&context->program, 0, sizeof(bfg_program_t));
    memset(&context->processor, 0, sizeof(bfg_processor_t));

    status = bfgInitParser((bfg_context)context);
    if( status != BFG_SUCCESS)
    {
        free(context);
        BFG_PRINT("Parser initialization failure!\n");
        return NULL;
    }
    return (bfg_context)context;
}

bfg_status  bfgReleaseContext(bfg_context* context)
{
    BFG_CHECK_NULL(context);
    BFG_CHECK_NULL(*context);

    bfgReleaseStack(&((bfg_context_t*)*context)->stack);
    bfgReleaseParser(*context);
    free(*context);
    return BFG_SUCCESS;
}

