// prsr.h
#ifndef PARSER_H
#define PARSER_H

#include "defaults.h" // Includes Flags enum and Prog struct definitions

// Struct to hold all command-line arguments and program state
typedef struct
{
    Flags flags;    // Bitmask flags controlling program behavior (CFG_*)
    Prog prog;      // Compiler availability info (GCC/Clang)

    char **files;       // Array of input file paths
    int file_count;     // Number of input files

    char **sym;         // Array of symbols for focus/highlight
    int sym_count;      // Number of symbols

    char **prog_args;   // Arguments to pass to the compiled program
    int prog_arg_count; // Number of program arguments

} Args;

// Initialize an Args struct with default values
void init_args(Args *args);

// Parse command-line arguments (argc, argv) and populate Args struct
void parse_args(int argc, char **argv, Args *args);

#endif // PARSER_H