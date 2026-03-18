#include <stdio.h>
#include <defaults.h>

int main(void)
{
    Prog prog;
    config_detect_compiler(&prog);

    printf("GCC %d, Clang %d\n", prog.has_gcc, prog.has_clang);

if(prog.has_gcc || prog.has_clang) printf("At least one compiler detected.\n");
else printf("No compilers detected.\n");
    return 0;
}
