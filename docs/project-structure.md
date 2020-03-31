# Project Directory Structure

This repository has the following directory structure.

```
.
├── docs/
├── samples/
├── src/
│   ├── cli/
│   └── core/
│       ├── headers/
│       │   ├── platforms/
│       │   └── structures/
│       ├── platforms/
│       │   └── linux/
│       └── structures/
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

The `src/cli` directory contains the code specific for the interpreter's
command-line application.

The `src/core` directory contains the code for the inner workings of the interpreter:
* This is the back-end of the interpreter.
* The `src/core` directory contains the code to parse Snowflake code, and 
  execute Snowflake code.
* The `src/core/headers` contains all the `.h` files.
* The `src/core/platforms` directory contains the code that changes depending
  on the platform (eg. `linux` or `arduino`).
* The `src/core/structures` directory contains the data structures and the functions
  to manipulate them, such as for Banks, Instructions, and the Program.
