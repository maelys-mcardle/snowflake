# Snowflake

Snowflake is a programming language devised for microcontrollers and is a paradigm that sits
somewhere between machine code and BASIC. It was developed for fun by [Maëlys McArdle][1].

This repository contains a default interpreter implementation. Documentation on how to 
code with the language is found in the [docs][2] sub-directory.

[1]: https://www.maelys.bio/
[2]: docs/

## Interpreter

This project comes with an interpreter to parse and execute Snowflake code.

### Compile

To compile the interpreter, run the command:
```
make
```

**Compilation of the interpreter requires [make][3], a C compiler with [c11][4] support, as well as [glibc][5].**

[3]: https://en.wikipedia.org/wiki/Make_(software)
[4]: https://en.wikipedia.org/wiki/C11_(C_standard_revision)
[5]: https://en.wikipedia.org/wiki/GNU_C_Library

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

The `src/cli` directory contains the code specific for the command-line program 
(`main.c`, the code to read command-line arguments, print code, and read local files.) 
The `headers` directory is specific to the header files for that command-line code.

The `src/core` directory contains the interface-independent code for the interpreter.
This handles parsing the code, running it, in a platform-independent way. Code
that is platform-dependent (eg. `linux` or `arduino`) is placed in the `src/core/platforms`
directory.

The `test` directory contains Snowflake files and their expected results to make
sure the interpeter is working as expected.
