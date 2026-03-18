#include <stdio.h>
#include "prsr.h"

int main(void)
{
    char *test_argv[] = {
        "--focus", "main",
        "--color",
        "test/hello.c",
        "--",
        "-Wall",
        "-Wextra",
        "-g",
        "-Iinclude"
    };

    int test_argc = sizeof(test_argv) / sizeof(test_argv[0]);

    Args args;

    parse_args(test_argc, test_argv, &args);

    printf("Flags: %d\n", args.flags);

    printf("\nSymbols (%d):\n", args.sym_count);
    for(int i = 0; i < args.sym_count; i++)
        printf("  %s\n", args.sym[i]);

    printf("\nFiles (%d):\n", args.file_count);
    for(int i = 0; i < args.file_count; i++)
        printf("  %s\n", args.files[i]);

    printf("\nProgram args (%d):\n", args.prog_arg_count);
    for(int i = 0; i < args.prog_arg_count; i++)
        printf("  %s\n", args.prog_args[i]);

    return 0;
}