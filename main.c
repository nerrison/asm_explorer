#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int has_gcc = (system("gcc --version >nul 2>&1") == 0);
    int has_clang = (system("clang --version >nul 2>&1") == 0);

    char command[256];

    if (has_gcc)
    {
        snprintf(command, sizeof(command),
                 "gcc -S -O0 -masm=intel array_to_array.c -o tmp.s");
        printf("> Using GCC\n");
        system(command); // generate tmp.s
    }
    else if (has_clang)
    {
        snprintf(command, sizeof(command),
                 "clang -S -O0 -masm=intel array_to_array.c -o tmp.s");
        printf("> Using Clang\n");
        system(command); // generate tmp.s
    }
    else
    {
        fprintf(stderr, "No compiler installed\n");
        return 1;
    }

    FILE *fp = fopen("tmp.s", "r");
    if (!fp)
    {
        perror("> fopen failed");
        return 1;
    }

    // Read in 256-byte chunks and flush immediately
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp))
    {
        fputs(buffer, stdout);
        fflush(stdout);  // flush immediately to console
    }

    fclose(fp);

    printf("\n> Done printing full assembly\n");
    system("pause");
    return 0;
}