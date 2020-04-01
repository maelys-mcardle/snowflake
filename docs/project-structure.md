# Project Directory Structure

This repository has the following directory structure.

```
.
├── docs/
├── samples/
├── src/
│   ├── include/
│   │   ├── platforms/
│   │   └── core/
│   └── interpreter/
│       ├── platforms/
│       │   └── linux/
│       └── core/
├── test/
├── LICENSE
├── Makefile
└── README.md

```

The root project directory contains the following:
* The `docs` directory contains documentation for how to code in Snowflake.
* The `samples` directory contains example Snowflake code files.
* The `src` directory contains all the code for the interpreter. 
* The `test` directory contains Snowflake files that test that the interpreter
  itself doesn't have any bugs.
* The `LICENSE` file contains the copyright license for the project.
* The `Makefile` file is the script to compile the interpreter.
* The `README.md` file contains information about this project.

## The `src` directory

The `src/` directory contains the code specific for the interpreter's
command-line application. The front-end are in the `main.c` and `main.h`
files.

The `src/interpreter` directory contains the code for parsing, printing and
running Snowflake code. Similarly:
* The `src/interpreter/core` directory contains the basic data structures and 
  the functions to manipulate them, such as for Banks, Instructions, and the Program.
* The `src/interpreter/platforms` directory contains the code that changes depending
  on the platform (eg. `linux` or `arduino`).

The `src/include` directory contains the header files for the `src/interpreter`.
* The `src/include/core` directory contains the header files for
  `src/interpreter/core`.
* The `src/include/platforms` contains the header files for 
  `src/interpreter/platforms`.