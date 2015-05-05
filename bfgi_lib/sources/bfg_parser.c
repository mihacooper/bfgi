#include "bfg_internal.h"

extern bfg_kernel_desc_t move_up_desc;
extern bfg_kernel_desc_t move_down_desc;
extern bfg_kernel_desc_t move_left_desc;
extern bfg_kernel_desc_t move_right_desc;
extern bfg_kernel_desc_t finish_desc;
extern bfg_kernel_desc_t empty_desc;
extern bfg_kernel_desc_t number_desc;
extern bfg_kernel_desc_t print_num_desc;
extern bfg_kernel_desc_t print_char_desc;
extern bfg_kernel_desc_t add_desc;
extern bfg_kernel_desc_t sub_desc;
extern bfg_kernel_desc_t mul_desc;
extern bfg_kernel_desc_t div_desc;
extern bfg_kernel_desc_t mod_desc;
extern bfg_kernel_desc_t lt_desc;
extern bfg_kernel_desc_t not_desc;


static bfg_kernel_desc_t* target_kernels[] =
{
    &move_up_desc,
    &move_down_desc,
    &move_left_desc,
    &move_right_desc,
    &finish_desc,
    &empty_desc,
    &number_desc,
    &print_num_desc,
    &print_char_desc,
    &add_desc,
    &sub_desc,
    &mul_desc,
    &div_desc,
    &mod_desc,
    &lt_desc,
    &not_desc,
};

bfg_kernel bfgParseCommand(bfg_context context, bfg_char ch_cmd)
{
    bfg_kernel_t* kernel = &((bfg_context_t*)context)->parser.kernels[ch_cmd];
    return (bfg_kernel)kernel;
}

bfg_status bfgInitParser(bfg_context context)
{
    BFG_CHECK_NULL(context);

    int i, j;
    for(i = 0; i < dimof(target_kernels); i++)
    {
        void** kernel_memory = &((bfg_context_t*)context)->parser.kernels_memory[i];
        *kernel_memory = NULL;
        if(target_kernels[i]->mem_size > 0)
            *kernel_memory = malloc(target_kernels[i]->mem_size);

        for(j = 0; j < target_kernels[i]->char_cmds_size; j++)
        {
            bfg_char ch_cmd = target_kernels[i]->char_cmds[j];
            bfg_kernel_t* kernel = &((bfg_context_t*)context)->parser.kernels[ch_cmd];
            if(kernel->func != NULL)
                BFG_PRINT("Warning: redeclaration of \'%c\' command", ch_cmd);
            if(target_kernels[i]->func == NULL)
                BFG_PRINT("Error: NULL kernel function(\'%c\')", ch_cmd);
            kernel->func       = target_kernels[i]->func;
            kernel->data_size  = target_kernels[i]->mem_size;
            kernel->mem        = *kernel_memory;
            kernel->mem_init   = target_kernels[i]->mem_init;
            kernel->mem_deinit = target_kernels[i]->mem_deinit;
            if(kernel->mem_init)
                kernel->mem_init(kernel->mem, kernel->data_size);
        }
    }
    ((bfg_context_t*)context)->parser.parse_func = (bfg_parse_func_t)&bfgParseCommand;
    ((bfg_context_t*)context)->parser.def_parse_func = (bfg_parse_func_t)&bfgParseCommand;
    return BFG_SUCCESS;
}

bfg_kernel bfgQueryKernelData(bfg_context context, bfg_char ch_cmd)
{
    bfg_kernel_t* kernel = &((bfg_context_t*)context)->parser.kernels[ch_cmd];
    return (bfg_kernel)kernel;
}

bfg_status bfgReleaseParser(bfg_context context)
{
    int i;
    for(i = 0; i < dimof(target_kernels); i++)
    {
        void* kernel_memory = ((bfg_context_t*)context)->parser.kernels_memory[i];
        bfg_kernel_desc_t* kernel = target_kernels[i];
        if(kernel_memory)
        {
            if(kernel->mem_deinit)
                kernel->mem_deinit(kernel_memory, kernel->mem_size);
            free(kernel_memory);
        }
    }
    return BFG_SUCCESS;
}

