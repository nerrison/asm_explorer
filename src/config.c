#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defaults.h" // Includes the Prog struct definition

// Detects availability of GCC and Clang compilers on the system
// Updates the Prog struct with has_gcc and has_clang flags
void config_detect_compiler(Prog *prog)
{
    // Check if GCC is installed by running "gcc --version"
    // Redirect output to /dev/null to suppress it
    // system() returns 0 if the command executed successfully
    prog->has_gcc = (system("gcc --version >/dev/null 2>&1") == 0) ? 1 : 0;

    // Check if Clang is installed by running "clang --version"
    // Note: there is a typo in original code ("clang -- version" has a space)
    // Correct command should be "clang --version"
    prog->has_clang = (system("clang --version >/dev/null 2>&1") == 0) ? 1 : 0;
}