# Snowflake Interpreter

This is an interpreter for the [Snowflake programming language][1], a language devised 
for devices with a numeric keypad for input.

**Compilation requires [make][2], a C compiler with [c11][3] support, as well as [glibc][4].**

[1]: https://github.com/maelys-mcardle/microprocessor-trainer/tree/master/docs/snowflake
[2]: https://en.wikipedia.org/wiki/Make_(software)
[3]: https://en.wikipedia.org/wiki/C11_(C_standard_revision)
[4]: https://en.wikipedia.org/wiki/GNU_C_Library

## Compile

To compile the interpreter, run the command:
```console
make
```

## Run

To run a Snowflake program, execute:
```console
./snowflake --file your-code-file.sn --run
```

To see how the interpreter understands the code file, run:
```console
./snowflake --file your-code-file.sn --show-code
```

If you run into issues, use the `--debug` option on the code. It will give more
information about how the interpreter understood the code, and what it was running:
```console
./snowflake --file your-code-file.sn --show-code --run --debug
```

## Clean

To delete files created during compilation, run the command:
```console
make clean
```
