#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "prsr.h"

// -----------------------
// Helper: check if filename has given extension
// -----------------------
int has_extension(const char *filename, const char *ext)
{
    size_t len = strlen(filename);
    size_t ext_len = strlen(ext);

    if(len < ext_len) return 0; // filename shorter than extension
    return strcmp(filename + len - ext_len, ext) == 0;
}

// Check if a file is a C source file (.c)
int is_src_file(const char *filename)
{
    return has_extension(filename, ".c");
}

// -----------------------
// Initialize Args struct with default values
// -----------------------
void init_args(Args *args)
{
    args->flags = CFG_NONE;

    args->files = NULL;
    args->file_count = 0;

    args->prog_arg_count = 0;
    args->prog_args = NULL;

    args->sym_count = 0;
    args->sym = NULL;
}

// -----------------------
// Parse command-line arguments and populate Args struct
// -----------------------
void parse_args(int argc, char **argv, Args *args)
{
    init_args(args); // start with defaults

    for(int i = 1; i < argc; i++)
    {
        // Watch mode
        if(strcmp(argv[i], "--watch") == 0)
        {
            args->flags |= CFG_WATCH;
        }
        // Focus symbols
        else if(strcmp(argv[i], "--focus") == 0)
        {
            args->flags |= CFG_FOCUS;

            int start = i + 1;
            int count = 0;

            // Collect symbols until a flag or source file is encountered
            while(start + count < argc && argv[start + count][0] != '-' && !is_src_file(argv[start + count]))
            {
                count++;
            }

            args->sym = malloc(sizeof(char*) * count);
            for(int j = 0; j < count; j++)
            {
                args->sym[j] = argv[start + j];
            }
            args->sym_count = count;
            i += count; // skip over processed symbols
        }
        // Strip assembler noise
        else if(strcmp(argv[i], "--strip") == 0)
        {
            args->flags |= CFG_STRIP;
        }
        // Instruction count per function
        else if(strcmp(argv[i], "--size") == 0)
        {
            args->flags |= CFG_SIZE;
        }
        // Save assembly to .s file
        else if(strcmp(argv[i], "--Sasm") == 0)
        {
            args->flags |= CFG_SAVE;
        }
        // Source files
        else if(is_src_file(argv[i]))
        {
            args->files = realloc(args->files, sizeof(char*) * (args->file_count + 1));
            args->files[args->file_count] = argv[i];
            args->file_count++;
        }
        // Arguments to pass to compiler after '--'
        else if(strcmp(argv[i], "--") == 0)
        {
            i++; // skip '--'
            while(i < argc)
            {
                args->prog_args = realloc(args->prog_args, sizeof(char*) * (args->prog_arg_count + 1));
                args->prog_args[args->prog_arg_count++] = argv[i];
                i++;
            }
            break; // all remaining arguments consumed
        }
        // Unknown arguments
        else
        {
            printf("Warning: unrecognized argument '%s'\n", argv[i]);
        }
    }
}