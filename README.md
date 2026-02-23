# ASM Explorer

**ASM Explorer** is a small C program that reads a C source file and prints its assembly output in Intel syntax.

This project is currently a **learning-stage basis**, designed to help explore how C code translates into assembly instructions, including loops, conditionals, and array operations. Future improvements will include more structured logic, support for different input files, and cleaner output handling.

---

## Features (Current)

- Detects whether **GCC** or **Clang** is installed.
- Generates assembly with `-O0` (no optimization) in Intel syntax.
- Prints `.rdata` and `.text` sections of the generated assembly.
- Uses `system("pause")` to keep console open after printing.
- Reads the generated `.s` file and flushes output immediately to terminal.

---

## Requirements

- **GCC** or **Clang** installed on your system
- A terminal on Windows (or adjust for Linux / Mac)
- C compiler able to generate Intel-syntax assembly

---

## Usage

1. Place your C source file (example: `array_to_array.c`) in the same folder as `main.c`.
2. Compile `main.c` with your preferred C compiler:

```bash
gcc main.c -o asm_explorer.exe
```

3. Run the program:

```bash
./asm_explorer.exe
```

4. The program will generate tmp.s and print the assembly output to the console. Press any key when done (due to `system("pause")`).

\> Notes / Future Work

- Currently only works with hardcoded source file names (array_to_array.c).
- Intended as a learning tool — later versions will allow selecting files dynamically, better parsing, or more advanced assembly exploration features.
- Generated `.s` files are ignored in GitHub via .gitignore to keep the repo clean

---

## Author

NERRISON