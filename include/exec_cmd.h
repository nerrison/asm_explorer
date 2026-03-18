// exec_cmd.h
#ifndef EXEC_CMD_H
#define EXEC_CMD_H

#include "prsr.h" // Header for command-line parsing (Args struct, etc.)
#include "flgs.h" // Header for flag definitions

// ANSI color codes for terminal output
#define RED   "\x1b[31m" // Red text (for errors or warnings)
#define GREEN "\x1b[32m" // Green text (for success messages)
#define RESET "\x1b[0m"  // Reset text color to default

// Struct to track differences between lines of assembly/code
typedef struct
{
    size_t prev_size;  // Number of lines in the previous snapshot
    char **prev_line;  // Pointer to previous lines (array of strings)
} Diff;

// Compares a new set of lines with the previous snapshot
// Updates the Diff struct with any changes
void diff_asm(Diff *diff, char **new_line, size_t new_size);

// Executes a command given by cmd_argv array with optional arguments
// Args struct (from prsr.h) can modify behavior of execution
void execute_cmd(char **cmd_argv, Args *args);

#endif // EXEC_CMD_H