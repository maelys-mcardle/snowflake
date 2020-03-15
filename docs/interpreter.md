# Interpreter

This project comes with an interpreter to execute Snowflake code. 
To be able to use it, it first needs to be **compiled**.

## Compile Interpreter

Compilation of the interpreter requires [make][4], a C compiler 
with [c11][5] support, as well as [glibc][6].

To compile the interpreter, run the command from the project root:
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

## Run Snowflake Programs

To execute a Snowflake program, use the `--run` or `-r` option:

```
./snowflake --run samples/hello-world.sn
```

The interpreter will run the code:

```
HELLO WORLD!
```

### Display Snowflake Code

Snowflake programs are largely written using digits. To see the parsed code with 
mnemonics and variable names substituted, use the `--print` or `-p` option:

```
./snowflake --print samples/hello-world.sn
```

The interpreter will produce the parsed version:

```
VAR @00 HELLO WORLD!
 << OUT @00
```

## Debug Snowflake Programs

If a Snowflake program isn't parsed or executed as expected, use
the `--debug` or `-d` option. This will give in-depth information 
about what the interpreter is doing at each step. The debug build of 
the interpreter is not required.

```
./snowflake --print --run --debug your-snowflake-program.sn
```

## Clean Interpreter Compilation Files

To delete files created during compilation, run the command:

```
make clean
```
