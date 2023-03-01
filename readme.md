C90 to MIPS compiler
============================================

The program reads C source code from a file, and write MIPS assembly to another file.

Program build and execution
---------------------------

The program is built by running the following command in the top-level directory of your repo:

    make bin/c_compiler

The compilation function is invoked using the flag `-S`, with the source file and output file specified on the command line:

    bin/c_compiler -S [source-file.c] -o [dest-file.s]

Input 
-----

The input file will be pre-processed [ANSI C](https://en.wikipedia.org/wiki/ANSI_C), also called C90 or C89 which is often used in embedded systems.

Basic features implemented:

* a file containing just a single function with no arguments
* variables of `int` type
* local variables
* arithmetic and logical expressions
* if-then-else statements
* while loops

Intermediate and advanced features implemented:

* files containing multiple functions that call each other
* functions that take up to four parameters
* for loops
* * the `sizeof(...)` function (for ints)

Other intermediate features not implemented:

* arrays declared globally (i.e. outside of any function in your file)
* arrays declared locally (i.e. inside a function)
* reading and writing elements of an array
* recursive function calls
* the `enum` keyword
* `switch` statements
* the `break` and `continue` keywords

Advanced features not implemented:

* variables of `double`, `float`, `char`, `unsigned`, structs, and pointer types
* calling externally-defined functions (i.e. the file being compiled declares a function, but its definition is provided in a different file that is linked in later on)
* functions that take more than four parameters
* mutually recursive function calls
* locally scoped variable declarations (e.g. a variable that is declared inside the body of a while loop, such as `while(...) { int x = ...; ... }`.
* the `typedef` keyword
* the `sizeof(...)` function (for other types, which takes either a type or a variable)
* taking the address of a variable using the `&` operator
* dereferencing a pointer-variable using the `*` operator
* pointer arithmetic
* character literals, including escape sequences like `\n`
* strings (as NULL-terminated character arrays)
* declaration and use of structs

Non-exhaustive ist of features that will not be tested.

* multithreading
* the `goto` keyword
* macros and other preprocessing directives
* the comma operator (for sequencing within expressions)
* the [old K&R style of declaring functions](https://stackoverflow.com/a/18820829)
* union types
* variable-length arrays
* the `const` keyword
* function pointers
* both implicit and explicit casting

Output Format
-------------

The output format should be MIPS1 assembly code.

It should be possible to assemble and link this code against a C run-time, and have it execute correctly on a MIPS processor as emulated by `qemu-mips`.

For instance, suppose I have a file called `test_program.c` that contains:

    int f() { return 10; }
    
and another file called `test_program_driver.c` that contains:

    int f();
    int main() { return !( 10 == f() ); }
    
I run the compiler on the test program, like so:

    bin/c_compiler -S test_program.c -o test_program.s
    
I then use GCC to assemble the generated assembly program (`test_program.s`), like so:

    mips-linux-gnu-gcc -mfp32 -o test_program.o -c test_program.s
    
I then use GCC to link the generated object file (`test_program.o`) with the driver program (`test_program_driver.c`), to produce an executable (`test_program`), like so:

    mips-linux-gnu-gcc -mfp32 -static -o test_program test_program.o test_program_driver.c

I then use QEMU to simulate the executable on MIPS, like so:

    qemu-mips test_program
    
This command should produce the exit code `0`.
