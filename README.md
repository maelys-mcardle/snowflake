# Snowflake

Snowflake is an interpreted programming language made for microcontrollers. The language itself
occupies the space in between machine code and BASIC. It was developed for fun by [Maëlys McArdle][1].

This repository contains an implementation of the interpreter. Documentation on how to 
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

To compile with debug symbols run the command:
```
make debug
```

[4]: https://en.wikipedia.org/wiki/Make_(software)
[5]: https://en.wikipedia.org/wiki/C11_(C_standard_revision)
[6]: https://en.wikipedia.org/wiki/GNU_C_Library

### Pretty-Print

Snowflake programs are largely written using digits. To see the prettyprinted version of this code,
with mnemonics and variable names substituted, use the `--print` or `-p` option:

```
./snowflake --print samples/hello-world.sn
```

The interpreter will produce the pretty-printed version:

```
VAR @00 HELLO WORLD!
 << OUT @00
```

### Run

To execute a Snowflake program, use the `--run` or `-r` option:

```
./snowflake --run samples/hello-world.sn
```

The interpreter will run the code:

```
HELLO WORLD!
```

### Debug

If your Snowflake program isn't parsed or executed as expected, you can use
the `--debug` or `-d` option. This will give in-depth information about what 
the interpreter is doing at each step. You do not need the debug build of 
the interpreter to use this flag:

```
./snowflake --print --run --debug your-snowflake-program.sn
```

### Clean

To delete files created during compilation, run the command:
```
make clean
```
