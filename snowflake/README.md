# Snowflake Interpreter

This is an interpreter for the [Snowflake programming language][1], a language devised 
for devices with a numeric keypad for input.

**Compilation requires [make][2], a C compiler with [c11][3] support, as well as [glibc][4].**

[1]: https://github.com/maelys-mcardle/microprocessor-trainer/tree/master/docs/snowflake
[2]: https://en.wikipedia.org/wiki/Make_(software)
[3]: https://en.wikipedia.org/wiki/C11_(C_standard_revision)
[4]: https://en.wikipedia.org/wiki/GNU_C_Library

## Running the Interpreter

### Compile

To compile the interpreter, run the command:
```
make
```

### Run

To run a Snowflake program, execute:
```
./snowflake --file your-code-file.sn --run
```

To see how the interpreter understands the code file, run:
```
./snowflake --file your-code-file.sn --print
```

If you run into issues, use the `--debug` option on the code. It will give more
information about how the interpreter understood the code, and what it was running:
```
./snowflake --file your-code-file.sn --print --run --debug
```

### Clean

To delete files created during compilation, run the command:
```
make clean
```

## Directory Structure

The interpreter has the following directory structure.

```
.
├── docs
│   └── examples
├── src
│   ├── cli
│   │   └── headers
│   └── core
│       ├── headers
│       └── platforms
│           └── linux
└── test
```

The root directory contains this `README` and `Makefile`.

The `docs` directory contains documentation for how to code in Snowflake.

The `src` directory contains all the code for the project. 

The `cli` directory contains the code specific for the command-line program 
(`main.c`, the code to read command-line arguments, print code, and read local files.) 
The `headers` directory is specific to the header files for that command-line code.

The `core` directory contains the interface-independent code for the interpreter.
This handles parsing the code, running it, in a platform-independent way. Code
that is platform-dependent (eg. `linux` or `arduino`) is placed in the `platforms`
directory.

The `test` directory contains Snowflake files and their expected results to make
sure the interpeter is working as expected.