// flgs.h
#ifndef PROG_FLGS_H
#define PROG_FLGS_H

#include "prsr.h" // Header for command-line argument parsing (Args struct)

// Struct to support the "watch" feature
typedef struct
{
    int wd;             // Watch descriptor or flag indicating active watch
    char **watched_path; // Array of paths currently being watched
} Watch;

// Display usage or help information for the program
void usgx1(void);

// Watch files for changes and optionally trigger recompilation
// Returns non-zero on error, 0 on success
int wthx1(Args *args, Watch *watch /*, char **cmd_argv*/);

// Save the given output line to a file (typically .s assembly file)
void svx1(const char *line, Args *args);

// Highlight only the specified symbols in the given line
// Useful for focusing on certain functions or variables
void fcsx1(const char *line, char **symbols, int sym_count);

// Clean the line by removing lines starting with a dot
// Typically removes assembly directives like ".text", ".globl", etc.
void clnx1(char *line);

// Count instructions in a function line and update the count
// Can be used for size analysis or instruction metrics
void szx1(char *line, int *count);

#endif // PROG_FLGS_H