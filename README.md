# ASM Explorer

**ASM Explorer** is a lightweight C program that compiles C source files and prints their assembly output in **Intel syntax**. It is designed as a learning tool to explore how C code translates into assembly instructions.  

This project currently supports **GCC** and **Clang** and is ideal for anyone learning C, assembly, or compiler behavior.

---

## Features

- **Detects installed compilers** (GCC or Clang).  
- **Generates assembly** using `-S` with Intel syntax (`-masm=intel`).  
- **Dynamic compiler selection**: prompts user if both GCC and Clang are installed.  
- **Watch mode**: automatically recompiles when source file changes and shows diff.  
- **Focus mode**: highlight specific functions or symbols while dimming other lines.  
- **Strip mode**: removes common assembly noise (`.cfi`, `.file`, `.ident`).  
- **Instruction count**: shows the number of instructions per function.  
- **Save assembly**: writes output to `.s` files instead of only printing to console.  

---

## How It Works

- Detects installed compiler(s) (GCC/Clang).
- Builds a dynamic compile command for the source file(s).
- Executes the compiler command, capturing assembly output.
- Processes output according to user flags (focus, strip, size, save).
- In watch mode, automatically detects file changes and shows differences in assembly.

---

## Requirements

- **GCC** or **Clang** installed on your system.  
- Terminal environment  
- C compiler capable of generating Intel-syntax assembly (`-masm=intel`).  

---

## Quick Start

### 1. Compile ASM Explorer

```bash
make           # Build the project
make run       # Run ASM Explorer
make clean     # Remove executable and temporary files
```

### 2. Run ASM Explorer

```bash
./asm_explorer [options] <source_file> -- [compiler flags]
```

### 3. Options

| Option          | Description                                              |
| --------------- | -------------------------------------------------------- |
| `--help`        | Show usage information                                   |
| `--watch`       | Recompile when source file changes and show diff         |
| `--focus <SYM>` | Highlight a specific function or symbol                  |
| `--strip`       | Remove common assembly noise (`.cfi`, `.file`, `.ident`) |
| `--size`        | Show instruction count per function                      |
| `--Sasm`        | Save assembly output to `.s` file(s)                     |


### 4. Examples

#### Compile a single file and print assembly

```bash
./asm_explorer dir/file.c
```

#### Strip assembly noise

```bash
./asm_explorer --strip dir/file.c
```

#### Highlight function "foo" and show instruction count

```bash
./asm_explorer --focus foo --size dir/file.c
```

#### Watch mode with extra compiler flags

```bash
./asm_explorer --watch dir/file.c -- -Wall -Wextra -g -Iinclude
```

---

## Notes & Future Improvements

> Designed primarily for learning and exploration.

- Watch mode currently relies on Linux/macOS inotify. Windows support may require adjustments.
-Future improvements may include:
- Cleaner and more structured assembly output
- Cross-platform file monitoring
-Support for multiple source files dynamically
- Advanced focus and filtering options

---

## Disclaimer

This project isn’t perfect — it’s a **learning-stage tool** designed to explore C and assembly.  
Some features (like watch mode) may have platform limitations, and output formatting can be rough.  
Future versions may improve cross-platform support, usability, and assembly presentation.

---

## Author

NERRISON
