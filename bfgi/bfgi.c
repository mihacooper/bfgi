#include "bfgl.h"

#define cols 7
#define rows 2

int main(int argc, char* argv[])
{
    bfg_context context = bfgCreateContext();
    bfg_char** code = (bfg_char**)malloc(sizeof(bfg_char*) * 2);
    int i,j;
    for(i = 0; i < 2;i++)
        code[i] = (bfg_char*)malloc(sizeof(bfg_char) * 4);
    code[0][0] = '>';
    code[0][1] = '1';
    code[0][2] = ' ';
    code[0][3] = '9';
    code[0][4] = ' ';
    code[0][5] = '2';
    code[0][6] = 'v';
    code[1][0] = '@';
    code[1][1] = ' ';
    code[1][2] = ' ';
    code[1][3] = '.';
    code[1][4] = ',';
    code[1][5] = '.';
    code[1][6] = '<';

    bfgLoadProgramCode(context, (bfg_char**)code, cols, rows, BFG_COPY);
    bfgExecuteProgram(context);
    bfgReleaseContext(&context);
    return 0;
}
