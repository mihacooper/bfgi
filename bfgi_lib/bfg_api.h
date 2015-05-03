#ifndef BFGL_API_H
#define BFGL_API_H

#include "types.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define BFG_PRINT(message, ...) { printf("[%s:%u] " message, __FUNCTION__, __LINE__, ##__VA_ARGS__); }
#define BFG_CHECK_NULL(var) \
    {\
        if((var) == NULL)\
        {\
            BFG_PRINT("Null reference of%s\n", " " #var);\
            return BFG_NULLREF;\
        }\
    }

//typedef bfg_context_t* bfg_context;

#endif // BFGL_API_H
