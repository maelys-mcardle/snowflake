# Directory Structure

This repository has the following directory structure.

```
.
├── docs
├── samples
├── src
│   ├── cli
│   │   └── headers
│   └── core
│       ├── headers
│       └── platforms
│           └── linux
└── test
```

The root directory contains a `README` and `Makefile`.

The `docs` directory contains documentation for how to code in Snowflake.

The `samples` directory contains example Snowflake code files.

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
