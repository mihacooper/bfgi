#include "bfgl.h"
#include "bfgl_api.h"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


int main(int argc, char* argv[])
{
    std::ifstream input(argv[1], std::ios::in);
    std::vector<std::string> scode;
    int max_length = 0;
    while(input.peek() != EOF)
    {
        std::string str;
        getline(input, str);
        max_length = std::max(max_length, (int)str.size());
        scode.push_back(str);
    }

    int cols = max_length, rows = scode.size();
    bfg_char** code = (bfg_char**)malloc(sizeof(bfg_char*) * rows);
    bfg_char** line = code;
    for(auto& it : scode)
    {
        it.resize(max_length);
        *line  = (bfg_char*)it.c_str();
        line++;
    }

    bfg_context context = bfgCreateContext();
    bfgLoadProgramCode(context, code, cols, rows, BFG_COPY);
    printf("Start\n");
    bfg_status status = bfgExecuteProgram(context);
    printf("\nFinish\n");
    if(status != BFG_EXE_DONE)
    {
        printf("\nStatus: %d\n", status);
    }
    bfgReleaseContext(&context);
    return 0;
}
