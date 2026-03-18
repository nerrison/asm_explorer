#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "build_cmd.h"

// Build a GCC/Clang compilation command dynamically based on Args
// Returns a NULL-terminated array of strings suitable for execvp
char **build_compile_cmd(Args *args)
{
    char *prog_name = NULL;

    // Decide which compiler to use
    if (args->prog.has_gcc && args->prog.has_clang)
    {
        // Both GCC and Clang are available; ask the user to pick one
        char choice[16];
        printf("Both GCC and CLANG are installed, pick one (gcc/clang): ");
        if (fgets(choice, sizeof(choice), stdin))
        {
            choice[strcspn(choice, "\n")] = 0; // remove newline
            if (strcmp(choice, "gcc") == 0 || strcmp(choice, "clang") == 0)
                prog_name = strdup(choice); // use user choice
            else
            {
                printf("Invalid choice, defaulting to GCC.\n");
                prog_name = strdup("gcc"); // fallback default
            }
        }
    }
    else if (args->prog.has_gcc)
        prog_name = strdup("gcc"); // only GCC available
    else if (args->prog.has_clang)
        prog_name = strdup("clang"); // only Clang available
    else
    {
        // No compiler installed
        fprintf(stderr, "Error: neither GCC nor CLANG installed!\n");
        return NULL;
    }

    printf("> Using %s\n", prog_name);

    // Allocate space for command-line arguments
    // Estimate total args: fixed flags + input files + program args
    int total_args = 10 + args->file_count + args->prog_arg_count;
    char **cmd_argv = malloc(sizeof(char*) * total_args);
    int idx = 0;

    // Compiler and compilation flags
    cmd_argv[idx++] = strdup(prog_name);     // compiler executable
    cmd_argv[idx++] = strdup("-S");          // generate assembly
    cmd_argv[idx++] = strdup("-masm=intel"); // use Intel syntax

    // Add input source files
    for (int i = 0; i < args->file_count; i++)
        cmd_argv[idx++] = strdup(args->files[i]);

    // Output to stdout (use "-" as placeholder)
    cmd_argv[idx++] = strdup("-o");
    cmd_argv[idx++] = strdup("-");

    // Add any extra arguments to pass to the compiler
    for (int i = 0; i < args->prog_arg_count; i++)
        cmd_argv[idx++] = strdup(args->prog_args[i]);

    cmd_argv[idx] = NULL; // NULL-terminate for execvp
    return cmd_argv;
}