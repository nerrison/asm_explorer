#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "flgs.h"      // flags/options (watch, strip, focus, size, save)
#include "prsr.h"      // argument parser (Args struct)
#include "defaults.h"  // compiler detection and config (Prog struct)
#include "build_cmd.h" // build compiler command (GCC/Clang)
#include "exec_cmd.h"  // execute command and process output

int main(int argc, char **argv)
{
    // -----------------------
    // No arguments -> show usage/help
    // -----------------------
    if (argc == 1)
    {
        usgx1();
        return 0;
    }

    // -----------------------
    // Check for explicit help flags
    // -----------------------
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0)
        {
            usgx1();
            return 0;
        }
    }

    // -----------------------
    // Parse CLI arguments
    // -----------------------
    Args args;
    init_args(&args);            // initialize defaults
    parse_args(argc, argv, &args); // populate flags, files, symbols, program args

    // -----------------------
    // Detect available compilers
    // -----------------------
    args.prog.has_gcc = 0;
    args.prog.has_clang = 0;
    config_detect_compiler(&args.prog);

    if (!args.prog.has_gcc && !args.prog.has_clang)
    {
        fprintf(stderr, "Error: neither GCC nor Clang is installed.\n");
        return 1;
    }

    // -----------------------
    // Build compiler command array
    // -----------------------
    char **cmd_argv = build_compile_cmd(&args);

    // -----------------------
    // Watch mode: continuously monitor files and recompile
    // -----------------------
    if (args.flags & CFG_WATCH)
    {
        Watch watch = {0};
        wthx1(&args, &watch); // blocking loop until Ctrl+C
    }
    else
    {
        // -----------------------
        // Execute compilation once
        // -----------------------
        execute_cmd(cmd_argv, &args);
    }

    // -----------------------
    // Free dynamically allocated arrays in Args
    // -----------------------
    free(args.files);
    free(args.sym);
    free(args.prog_args);

    return 0;
}