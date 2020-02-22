# Snowflake Interpreter

This is a Snowflake interpreter.

**This requires make and cc with c11 support.**

## Compile

To compile, run the command:
```
make
```

## Run

To run, execute:
```
./snowflake --file your-code-file.sn --run
```

To see how the interpreter understands the code file, run:
```
./snowflake --file your-code-file.s --show-code
```

If you run into issues, use the `--debug` option on the code. It will give more
information about how the interpreter understood the code, and what it was running:
```
./snowflake --file your-code-file.sn --show-code --debug
```

## Clean

To delete files created during compilation, run the command:
```
make clean
```
