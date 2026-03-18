// test_execute.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prsr.h"
#include "defaults.h"
#include "build_cmd.h"
#include "exec_cmd.h"
#include "flgs.h"

int main()
{
    // 1. Create a tiny dummy C file
    const char *filename = "test/hello.c";
    FILE *fp = fopen(filename, "w");
    if(!fp) { perror("fopen"); return 1; }
    fputs("int main(){return 0;}\n", fp);
    fclose(fp);

    // 2. Setup Args
    Args args;
    init_args(&args);
    args.files = malloc(sizeof(char*));
    args.files[0] = strdup(filename);
    args.file_count = 1;
    args.flags = CFG_STRIP; // apply strip flag as a test

    // 3. Detect compilers
    args.prog.has_gcc   = (system("gcc --version > /dev/null 2>&1") == 0) ? 1 : 0;
    args.prog.has_clang = (system("clang --version > /dev/null 2>&1") == 0) ? 1 : 0;

    if(!args.prog.has_gcc && !args.prog.has_clang)
    {
        fprintf(stderr,"No compiler detected!\n");
        return 1;
    }

    // 4. Build compile command
    char **cmd_argv = build_compile_cmd(&args);
    if(!cmd_argv) { fprintf(stderr,"Failed to build compile command\n"); return 1; }

    // 5. Execute
    execute_cmd(cmd_argv, &args);

    // 6. Cleanup
    free(args.files[0]);
    free(args.files);

    printf("Test completed successfully.\n");
    return 0;
}