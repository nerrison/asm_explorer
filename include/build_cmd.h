// build_cmd.h
#ifndef BUILD_CMD_H
#define BUILD_CMD_H

#include "prsr.h"

//build a gcc/clang command array from Args
char **build_compile_cmd(Args *args);

#endif //BUILD_CMD_H