# Snowflake File Format

The contents of a Snowflake file looks like this:

```
10 00 Hello, World!    ;; Store "Hello, World!" to Bank 00
03 00 00              ;; Output the contents of Bank 00 to the LCD
```

## File Extension

Snowflake programs have the `.sn` file extension by convention.

## Character Set

Snowflake files are plaintext.

Snowflake programs are stored in ASCII. UTF-8 is not supported with the included
interpreter implementation.

## Instructions

Each line is one instruction.

Lines in Snowflake have the following format:

```
INSTRUCTION                     ;; COMMENT
```

```
INSTRUCTION PARAMETER           ;; COMMENT
```

```
INSTRUCTION PARAMETER PARAMETER ;; COMMENT
```

The line is split into fields by whitespace:
* The first field is the instruction code. No mnemonics.
* The second field is a parameter.
* The third field is a parameter.

Parameters can be required, optional, or none. Parameters can specify a 
bank, device, type, label or literal. All except the literal are integers.

All whitespace at the beginning or end of a field is trimmed.

Any whitespace in a literal field is treated as part of that literal, 
except for the whitespace at the start or end, which is also trimmed.

## Comments

Anything that follows `;;` is treated as a comment and ignored. These comments
may not be displayed in an interpreter. Empty lines are ignored.
