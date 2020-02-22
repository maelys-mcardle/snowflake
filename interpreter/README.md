# Snowflake Interpreter

This is an interpreter for the [Snowflake programming language][1], a language devised 
for devices with a numeric keypad for input.

**Compilation requires make and cc with c11 support as well as [glibc][2]**

[1]: https://github.com/maelys-mcardle/microprocessor-trainer/tree/master/docs/snowflake
[2]: https://en.wikipedia.org/wiki/GNU_C_Library

## Compile

To compile the interpreter, run the command:
```
make
```

## Run

To run a Snowflake program, execute:
```
./snowflake --file your-code-file.sn --run
```

To see how the interpreter understands the code file, run:
```
./snowflake --file your-code-file.sn --show-code
```

If you run into issues, use the `--debug` option on the code. It will give more
information about how the interpreter understood the code, and what it was running:
```
./snowflake --file your-code-file.sn --show-code --run --debug
```

## Clean

To delete files created during compilation, run the command:
```
make clean
```
