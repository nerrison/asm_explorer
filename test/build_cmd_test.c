#include <stdio.h>
#include "build_cmd.h"

int main(void)
{
    //Create a fake Args struct for testing
    Args args;


    // set compiler detection manually for test
    args.prog.has_gcc = 1;
    args.prog.has_clang = 0;

    //add some test input files
    args.file_count = 2;
    char *files[] = {"test/hello.c", "test/add.c"};
    args.files = files;

    //add some extra prog args
    args.prog_arg_count = 3;
    char *prog_args[] = {"-Wall", "-g", "-Iinclude"};
    args.prog_args = prog_args;

    //  Build the command
    char **cmd = build_compile_cmd(&args);

    //Print the command array for verification
    printf("Command array:\n");
    for(int i = 0; i < 64 && cmd[i] != NULL; i++)
        printf("%s ", cmd[i]);
    printf("\n");

    return 0;
}