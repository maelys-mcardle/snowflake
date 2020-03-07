# Snowflake

Snowflake is a programming language devised for microcontrollers and is a paradigm that sits
somewhere between machine code and BASIC. It was developed for fun by [Maëlys McArdle][1].

This repository contains a default interpreter implementation. Documentation on how to 
code with the language is found in the [docs][2] directory. Examples of code written in
Snowflake is found in the [samples][3] directory.

[1]: https://www.maelys.bio/
[2]: docs/
[3]: samples/

## Interpreter

This project comes with an interpreter to parse and execute Snowflake code.

### Compile

Compilation of the interpreter requires [make][4], a C compiler with [c11][5] support, as well as [glibc][6].

To compile the interpreter, run the command:
```
make
```

[4]: https://en.wikipedia.org/wiki/Make_(software)
[5]: https://en.wikipedia.org/wiki/C11_(C_standard_revision)
[6]: https://en.wikipedia.org/wiki/GNU_C_Library

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
