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
./snowflake --file your-code-file.sn --print-code --run
```

If you run into issues, use the `--debug` option on the code:
```
./snowflake --file your-code-file.sn --print-code --debug
```

## Clean

To clean, run the command:
```
make clean
```