#ifndef __BFGL_H__
#define __BFGL_H__


#ifdef __cplusplus
extern "C"{
#endif

typedef unsigned int  bfg_size;
typedef unsigned char bfg_char;
typedef          int  bfg_int;

typedef struct bfg_context_t* bfg_context;
typedef struct bfg_stack_t*   bfg_stack;
typedef struct bfg_kernel_t*  bfg_kernel;

typedef enum
{
    bfg_false,
    bfg_true,
}bfg_bool;

typedef enum
{
    BFG_SUCCESS          = 0,
    BFG_FAILURE          = 1,
    BFG_EXE_DONE         = 2,
    BFG_NULLREF          = 3,
    BFG_FULLSTACK        = 4,
    BFG_LEAVE_FIELD      = 5,
    BFG_UNSUPPORTED_TYPE = 6,
    BFG_UNSUPPORTED_CMD  = 7,
    BFG_WRONG_MEM_SIZE   = 8,
    BFG_WRONG_DATA_TYPE  = 9,
    BFG_STACK_IS_EMPTY   = 10,
    BFG_PRINT_CHAR_ERROR = 11,
}bfg_status;

typedef enum
{
    BFG_COPY,
    BFG_PUT
}bfg_mem_type;

typedef enum
{
    BFG_DATA_SIMPLE,
    BFG_DATA_USER,
}bfg_data_type;


typedef bfg_status (*bfg_cmd_func_t)(bfg_context, void* data, bfg_size size);

typedef bfg_status (*bfg_kernel_mem_t)(void* data, bfg_size size);

typedef bfg_kernel (*bfg_parse_func_t)(bfg_context context, bfg_char ch_cmd);

typedef struct
{
    bfg_data_type type;
    void*         mem;
    bfg_size      data_size;
}bfg_data_t;

typedef struct
{
    bfg_int        x;
    bfg_int        y;
}bfg_point_t;

typedef struct
{
    bfg_char*        char_cmds;
    bfg_size         char_cmds_size;
    bfg_cmd_func_t   func;
    bfg_kernel_mem_t mem_init;
    bfg_kernel_mem_t mem_deinit;
    bfg_size         mem_size;
}bfg_kernel_desc_t;

#ifdef __cplusplus
}
#endif

#endif //__BFGL_H__
