#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/inotify.h>
#include <sys/select.h>
#include <time.h>

#include "flgs.h"
#include "build_cmd.h"
#include "exec_cmd.h"

// -----------------------
// Display usage/help info
// -----------------------
void usgx1()
{
    printf("asmXplr - minimal GCC/Clang assembly explorer (Intel Syntax)\n\n");

    printf("USAGE:\n");
    printf("    asmXplr [options] <file> -- [gcc/clang flags]\n\n");

    printf("DESCRIPTION:\n");
    printf("    Compiles <file> to assembly using either gcc or clang (-S).\n");
    printf("    Intel syntax is used.\n");
    printf("    Source <file> and all flags after '--' are forwarded to gcc or clang.\n\n");

    printf("OPTIONS:\n");
    printf("    --help          Shows usage\n");
    printf("    --watch         Recompile when file changes and show diff between previous and new assembly\n");
    printf("    --focus <SYM>   Highlight a symbol and dim the rest\n");
    printf("    --strip         Removes common assembly noise (.cfi, .file, .ident, etc.)\n");
    printf("    --size          Show instruction count per function\n");
    printf("    --Sasm          Write assembly to file instead of stdout\n\n");

    printf("EXAMPLES\n");
    printf("    asmXplr file.c\n");
    printf("    asmXplr --strip  file.c\n");
    printf("    asmXplr --focus foo --size file.c\n");
    printf("    asmXplr --watch  file.c -- -Wall -Wextra -g -Iinclude\n\n");

    printf("AUTHOR:\n");
    printf("    NERRISON\n");
}

// -----------------------
// Watch feature constants
// -----------------------
#define DEBOUNCE_MS 100 // debounce delay (not fully used)

// ---------------------------------
// --watch: monitor source file changes
// ---------------------------------
int wthx1(Args *args, Watch *watch /*, char **cmd_argv*/)
{
    int fd = inotify_init();
    if(fd == -1) { perror("inotify_init"); return -1; }

    // Allocate array to store watched paths
    watch->watched_path = malloc(sizeof(char*) * args->file_count);
    for(int i = 0; i < args->file_count; i++)
    {
        int wd = inotify_add_watch(fd, args->files[i],
                                   IN_DELETE | IN_CLOSE_WRITE); // watch for delete/write
        if(wd == -1) { perror("inotify_add_watch"); continue; }
        watch->wd = wd;
        watch->watched_path[i] = strdup(args->files[i]);
    }

    char buffer[1024];

    while(1)
    {
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(fd, &fds);

        // Wait up to 1 second for an inotify event
        struct timeval tv = {1, 0};
        int ret = select(fd+1, &fds, NULL, NULL, &tv);
        if(ret < 0) { perror("select"); break; }
        if(ret == 0) continue; // timeout, loop again

        printf("\x1b[2J\x1b[H"); // clear screen
        printf("> Watching files (press Ctrl+C to exit)...\n");

        int length = read(fd, buffer, sizeof(buffer));
        if(length < 0) { perror("read"); break; }

        // Rebuild compile command each time a change occurs
        char **cmd_copy = build_compile_cmd(args);
        execute_cmd(cmd_copy, args);

        printf("\n--- Recompiled at %ld ---\n\n", time(NULL));
    }

    usleep(200000); // slight delay

    // Free watched paths
    for(int i = 0; i < args->file_count; i++)
        free(watch->watched_path[i]);
    free(watch->watched_path);
    close(fd);

    return 0;
}

// -----------------------
// Save assembly line to .s file
// -----------------------
void svx1(const char *line, Args *args)
{
    for(int i = 0; i < args->file_count; i++)
    {
        if(!args->files[i]) continue;

        char out_file[256];
        strcpy(out_file, args->files[i]);

        // strip extension if it exists
        char *dot = strrchr(out_file, '.');
        if(dot) *dot = '\0';

        strcat(out_file, ".s"); // append .s extension

        FILE *fp = fopen(out_file, "a");
        if(!fp) { perror("fopen"); continue; }

        fputs(line, fp);
        fclose(fp);
    }
}

// -----------------------
// --focus: highlight only specified symbols
// -----------------------
void fcsx1(const char *line, char **symbols, int sym_count)
{
    static int in_func = 0;

    // Check if line starts a symbol to focus on
    for(int i = 0; i < sym_count; i++)
    {
        if(strstr(line, symbols[i]) && strchr(line, ':')) {
            in_func = 1;  // start highlighting
            break;
        }
    }

    // Stop highlighting at end of function
    if(in_func && strstr(line, ".cfi_endproc"))
        in_func = 0;

    if(in_func)
        printf("%s", line);           // highlighted
    else
        printf("\x1b[2m%s\x1b[0m", line);  // dimmed
}

// -----------------------
// --strip: remove lines starting with a dot
// -----------------------
void clnx1(char *line)
{
    if(!line) return;

    // skip leading whitespace
    int i = 0;
    while(line[i] && isspace((unsigned char)line[i])) i++;

    // if first non-space char is '.', blank the line
    if(line[i] == '.')
        line[0] = '\0';
}

// -----------------------
// szx1: count instructions per function
// -----------------------
void szx1(char *line, int *count)
{
    char *p = line;

    // skip leading whitespace
    while(*p && isspace((unsigned char)*p))
        p++;

    // ignore empty lines, comments, or labels
    if(*p == '\0' || *p == '\n' || *p == '#') return;

    // function label
    if(strchr(p, ':')) {
        if(*count > 0)
            printf("  ; %d instructions\n", *count);
        *count = 0;
        return;
    }

    // assembler directive
    if(*p == '.') return;

    (*count)++;  // count real instruction
}