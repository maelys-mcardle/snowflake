# Hello, World!

This is what "hello world" looks like in Snowflake:

```
10 01 Hello, World!   ;; Store "Hello, World!" in Bank 01
03 00 01              ;; Display the contents of Bank 01
```

## Breaking it down

### Instructions

Each line of Snowflake code is an instruction.

These lines in Snowflake have the following format:

```
INSTRUCTION [PARAMETER] [PARAMETER]
```

Instructions can have zero, one, or two parameters. All instructions
and their parameters are documented in the [reference documentation][1]. 
Comments are optional and follow a double semi-colon (`;;`),

### First line

This is the first line of code, omitting the comments:

```
10 01 Hello, World!
```

* `10` is the `VAR` instruction (see [reference documentation][1]).
  The `VAR` instruction is for putting data in a variable. It has two 
  parameters.
* `01` is what bank to store the data in, in this case Bank `01`.
* `Hello, World!` is what's being stored in the bank.

To help in reading this code after, [the interpreter][2] has a `--print` 
flag to help. This is what the first line of the code above looks like
when it's passed through the Snowflake interpreter with the `--print` flag:

```
VAR @00 Hello, World!
```

`VAR` for declaring a variable; the `@01` means bank `01`; and what follows is
the string that's stored in the bank.

### Second line

This is the second line of code, omitting the comments:

```
03 00 01
```

* `03` is the `<<` or output instruction. It's for sending data to a device
  (see [reference documentation][1]). It takes two parameters.
* `00` is `OUT` or the standard output device, which is the most common way of
  displaying data back to the user.
* `01` is what bank will have its contents sent to the output device, in this
  case Bank `01`.

This is what the second line of code looks like when it's passed 
through the Snowflake interpreter with the `--print` flag:

```
 << OUT @01
```

**Note:**

* An `@` in front of the `@01` denotes that it's referring to Bank 01.
* An `:` in front of the `:01` denotes that it's referring to Label 01.
* A lack of `@` or `:` in front of a number/string denotes that it's referring to a literal.

[1]: language-reference.md
[2]: interpreter.md
[3]: file-format.md
