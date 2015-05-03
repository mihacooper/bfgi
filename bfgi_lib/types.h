#ifndef TYPES_H
#define TYPES_H

#define STACK_PAGE_SIZE 1024
#define STACK_MAX_PAGES 512

#define TARGET_FUNC_SIZE 255

typedef unsigned int  bfg_size;
typedef unsigned char bfg_char;
typedef          int  bfg_int;

typedef enum
{
    bfg_false,
    bfg_true,
}bfg_bool;

typedef enum
{
    BFG_SUCCESS = 0,
    BFG_FAILURE,
    BFG_EXE_DONE,
    BFG_NULLREF,
    BFG_FULLSTACK,
    BFG_LEAVE_FIELD,
    BFG_UNSUPPORTED_TYPE,
    BFG_UNSUPPORTED_CMD,
    BFG_WRONG_MEM_SIZE,
    BFG_WRONG_DATA_TYPE,
    BFG_STACK_IS_EMPTY,
    BFG_PRINT_CHAR_ERROR,
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

typedef struct
{
    bfg_data_type type;
    void*         mem;
    bfg_size      data_size;
}bfg_data_t;

typedef struct
{
    bfg_data_t   mem[STACK_PAGE_SIZE];
    bfg_size     field;
}bfg_page_t;

typedef struct
{
    bfg_page_t*     pages[STACK_MAX_PAGES];
    bfg_size        capacity;
    bfg_size        page;
}bfg_stack_t;

typedef struct
{
    bfg_int        x;
    bfg_int        y;
}bfg_point_t;

typedef struct
{
    bfg_char**      code;
    bfg_size        rows;
    bfg_size        cols;
}bfg_program_t;

typedef struct bfg_context_t* bfg_context;
typedef bfg_status (*bfg_cmd_func_t)(bfg_context, void* data, bfg_size size);
typedef bfg_status (*bfg_kernel_mem_t)(void* data, bfg_size size);

typedef struct
{
    bfg_cmd_func_t   func;
    void*            mem;
    bfg_size         data_size;
    bfg_kernel_mem_t mem_init;
    bfg_kernel_mem_t mem_deinit;
}bfg_kernel_t;

typedef bfg_kernel_t (*bfg_parse_func_t)(bfg_context context, bfg_char ch_cmd);

typedef struct
{
    bfg_parse_func_t parse_func;
    bfg_kernel_t     kernels[TARGET_FUNC_SIZE];
    void*            kernels_memory[TARGET_FUNC_SIZE];
}bfg_parser_t;

typedef struct
{
    bfg_point_t      pos;
    bfg_point_t      shift;
    bfg_status   status;
}bfg_processor_t;

typedef struct
{
    bfg_char*        char_cmds;
    bfg_size         char_cmds_size;
    bfg_cmd_func_t   func;
    bfg_kernel_mem_t mem_init;
    bfg_kernel_mem_t mem_deinit;
    bfg_size         mem_size;
}bfg_kernel_desc_t;

typedef struct
{
    bfg_stack_t     stack;
    bfg_program_t   program;
    bfg_processor_t processor;
    bfg_parser_t    parser;
}bfg_context_t;

#define dimof(x) (sizeof(x) / sizeof((x)[0]))

#endif // TYPES_H
