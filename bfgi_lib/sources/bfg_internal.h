#ifndef TYPES_H
#define TYPES_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "bfgl.h"

#define dimof(x) (sizeof(x) / sizeof((x)[0]))

#define BFG_PRINT(message, ...) { printf("[%s:%u] " message, __FUNCTION__, __LINE__, ##__VA_ARGS__); }
#define BFG_CHECK_NULL(var) \
    {\
        if((var) == NULL)\
        {\
            BFG_PRINT("Null reference of%s\n", " " #var);\
            return BFG_NULLREF;\
        }\
    }

#ifndef STACK_PAGE_SIZE
    #define STACK_PAGE_SIZE 1024
#endif

#ifndef STACK_MAX_PAGES
    #define STACK_MAX_PAGES 512
#endif

#define TARGET_FUNC_SIZE 255

#include "bfgl.h"

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
    bfg_char**      code;
    bfg_size        rows;
    bfg_size        cols;
}bfg_program_t;


typedef struct
{
    bfg_cmd_func_t   func;
    void*            mem;
    bfg_size         data_size;
    bfg_kernel_mem_t mem_init;
    bfg_kernel_mem_t mem_deinit;
}bfg_kernel_t;

typedef struct
{
    bfg_parse_func_t parse_func;
    bfg_parse_func_t def_parse_func;
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
    bfg_stack_t     stack;
    bfg_program_t   program;
    bfg_processor_t processor;
    bfg_parser_t    parser;
}bfg_context_t;

#include "bfg_context.h"
#include "bfg_parser.h"
#include "bfg_stack.h"
#include "bfg_program.h"
#include "bfg_parser.h"

#endif // TYPES_H
