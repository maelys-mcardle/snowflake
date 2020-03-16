# Snowflake File Format

The contents of a Snowflake file looks like this:

```
10 00 Hello, World!   ;; Store "Hello, World!" to Bank 00
03 00 00              ;; Output the contents of Bank 00 to the LCD
```

## File Extension

Snowflake programs have the `.sn` file extension by convention.

## Character Set

Snowflake files are plaintext.

Snowflake programs are stored in ASCII. UTF-8 is not supported with the included
interpreter implementation.

## Comments

Anything that follows `;;` on a line is treated as a comment and ignored. These comments
may not be displayed in an interpreter.

## Instructions

Each line is one instruction. Empty lines are acceptable. Lines with only a comment are also acceptable.

Depending on the instruction, lines in Snowflake have the following format:

```
INSTRUCTION                     ;; COMMENT
```

...or:

```
INSTRUCTION PARAMETER           ;; COMMENT
```

...or:

```
INSTRUCTION PARAMETER PARAMETER ;; COMMENT
```

Comments are optional. Fields are split by whitespace. Parameters can specify a 
`TYPE`, `BANK`, `LABEL`, `DEVICE` or `LITERAL`. All except the literal are 
positive whole numbers. Literals can be whole numbers, decimal numbers, or
a string. Consult the [language reference][1] for more on types, banks, labels,
devices and literals.

Whitespace operates a little differently for literals. The whitespace preceding
or following a literal is discarded, but the whitespace in a literal (eg. the
string `cats are cute`) are preserved.

See the samples directory for examples of Snowflake files.

[1]: language-reference.md
