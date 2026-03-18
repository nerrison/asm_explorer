// defaults.h
#ifndef CONFIG_H
#define CONFIG_H

// Enum to define configuration flags using bitmasking
typedef enum {
    CFG_NONE  = 0,        // No configuration
    CFG_FOCUS = 1 << 0,   // Focus mode enabled
    CFG_WATCH = 1 << 1,   // Watch mode enabled
    CFG_SAVE  = 1 << 3,   // Save option enabled
    CFG_SIZE  = 1 << 4,   // Size-related option enabled
    CFG_STRIP = 1 << 5    // Strip option enabled
} Flags;

// Struct to indicate presence of specific compilers
typedef struct {
    int has_gcc;   // Non-zero if GCC compiler is available
    int has_clang; // Non-zero if Clang compiler is available
} Prog;

// Function prototype to detect available compilers
// Fills the Prog struct with information about GCC/Clang availability
void config_detect_compiler(Prog *prog);

#endif // CONFIG_H