# Snowflake

Snowflake is an interpreted programming language made for microcontrollers. The language itself
occupies the space in between machine code and BASIC.

This repository contains the following:

* Code to compile and run the interpreter. See below for more information.
* Documentation on how to code with the language. See the [docs][1] directory. 
* Examples of Snowflake programs. See the [samples][2] directory.

[1]: docs/
[2]: samples/

## Author

Snowflake was developed as a fun side-project by [Maëlys McArdle][1].

[3]: https://www.maelys.bio/

## Interpreter

This project comes with an interpreter to parse and execute Snowflake code.

### Compile Interpreter

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

### Show Pretty-Printed Snowflake Code

Snowflake programs are largely written using digits. To see the pretty-printed version of this code,
with mnemonics and variable names substituted, use the `--print` or `-p` option:

```
./snowflake --print samples/hello-world.sn
```

The interpreter will produce the pretty-printed version:

```
VAR @00 HELLO WORLD!
 << OUT @00
```

### Run Snowflake Programs

To execute a Snowflake program, use the `--run` or `-r` option:

```
./snowflake --run samples/hello-world.sn
```

The interpreter will run the code:

```
HELLO WORLD!
```

### Debug Snowflake Programs

If your Snowflake program isn't parsed or executed as expected, you can use
the `--debug` or `-d` option. This will give in-depth information about what 
the interpreter is doing at each step. You do not need the debug build of 
the interpreter to use this flag:

```
./snowflake --print --run --debug your-snowflake-program.sn
```

### Clean Interpreter Compilation Files

To delete files created during compilation, run the command:
```
make clean
```
