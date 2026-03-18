#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "exec_cmd.h"

// Compare new assembly lines to previous snapshot and highlight differences
// Prints removed lines in RED and added lines in GREEN
void diff_asm(Diff *diff, char **new_line, size_t new_size)
{
    size_t i = 0, j = 0;

    // Compare previous and new lines
    while(i < diff->prev_size || j < new_size)
    {
        if(i < diff->prev_size && j < new_size &&
           strcmp(diff->prev_line[i], new_line[j]) == 0)
        {
            // Lines are identical, move forward
            i++; j++;
        }
        else
        {
            // Line removed in new snapshot
            if(i < diff->prev_size)
                printf(RED "[-] %s" RESET "\n", diff->prev_line[i++]);
            // Line added in new snapshot
            if(j < new_size)
                printf(GREEN "[+] %s" RESET "\n", new_line[j++]);
        }
    }

    // Free memory of previous snapshot
    for(size_t k = 0; k < diff->prev_size; k++)
        free(diff->prev_line[k]);
    free(diff->prev_line);

    // Store new snapshot for next diff
    diff->prev_line = malloc(sizeof(char*) * new_size);
    for(size_t k = 0; k < new_size; k++)
        diff->prev_line[k] = strdup(new_line[k]);
    diff->prev_size = new_size;
}

// Execute a command and optionally process its output
void execute_cmd(char **cmd_argv, Args *args)
{
    if(!cmd_argv || !cmd_argv[0])
    {
        fprintf(stderr, "Error: command is empty!\n");
        return;
    }

    int pipefd[2];
    if(pipe(pipefd) < 0) { perror("pipe"); return; }

    pid_t pid = fork();
    if(pid < 0) { perror("fork"); return; }

    if(pid == 0) // child process
    {
        close(pipefd[0]);                 // close unused read end
        dup2(pipefd[1], STDOUT_FILENO);   // redirect stdout to pipe
        dup2(pipefd[1], STDERR_FILENO);   // redirect stderr to pipe
        close(pipefd[1]);                 // close original write end
        execvp(cmd_argv[0], cmd_argv);    // execute command
        perror("execvp");                 // if exec fails
        exit(1);
    }

    close(pipefd[1]); // parent closes write end

    FILE *pipe_stream = fdopen(pipefd[0], "r"); // read command output
    if(!pipe_stream) { perror("fdopen"); return; }

    static Diff diff = {0}; // persistent diff state for watch mode
    char buf[512];
    char **lines = NULL;
    size_t line_count = 0;

    // Read all lines from command output
    while(fgets(buf, sizeof(buf), pipe_stream))
    {
        lines = realloc(lines, sizeof(char*) * (line_count + 1));
        lines[line_count++] = strdup(buf);
    }

    fclose(pipe_stream);
    waitpid(pid, NULL, 0); // wait for child to finish

    // Show differences if watch mode is enabled
    if(args->flags & CFG_WATCH)
        diff_asm(&diff, lines, line_count);
    
    int instr_count = 0; // for CFG_SIZE option

    // Process each line according to flags
    for(size_t i = 0; i < line_count; i++)
    {
        char *line = lines[i];
        if(args->flags & CFG_STRIP) clnx1(line); // remove assembly directives
        if(args->flags & CFG_SIZE)  szx1(line, &instr_count); // count instructions
        if(args->flags & CFG_FOCUS) fcsx1(line, args->sym, args->sym_count); // highlight symbols
        else
            printf("%s", line); // default: print line

        if(args->flags & CFG_SAVE) // save line to file if requested
            svx1(line, args);

        free(line); // free duplicated line
    }
    free(lines);

    // Free dynamically allocated command arguments
    for(int i = 0; cmd_argv[i]; i++)
        free(cmd_argv[i]);
    free(cmd_argv);
}