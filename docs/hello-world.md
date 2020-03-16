# Hello, World!

This is what "hello world" looks like in Snowflake:

```
10 01 Hello, World!   ;; Store "Hello, World!" in Bank 01
03 00 01              ;; Display the contents of Bank 01
```

These lines in Snowflake have the following format:

```
INSTRUCTION PARAMETER PARAMETER ;; COMMENT
```

The number of parameters depends on the instruction. All instructions
and their parameters are documented in the [reference documentation][1]. Comments
are optional.

The first line of the hello world example has the `10` instruction code, which declares
a variable. Its first parameter defines where the variable is stored, in this case, 
bank `01`. The second parameter is what to store in the variable, in this case, the 
string `Hello, World!`. 

All these numbers do not make for readable code. [The interpreter][2] has a `--print` 
flag to help with this. This is what the first line of the code above looks like
when it's passed through the Snowflake interpreter with the `--print` flag:

```
VAR @00 Hello, World!
```

`VAR` for declaring a variable; the `@01` means bank `01`; and what follows is
the string that's stored in the bank.

The second line, instruction `03` is for sending data to a device. The first
parameter defines which device to send the information to. `00` means standard
output, which is the display. The second parameter is which bank will have its
contents sent to this device. In this case, bank `01`.

This is what the first two lines of the code looks like when it's passed 
through the Snowflake interpreter with the `--print` flag:

```
VAR @01 Hello, World!
 << OUT @01
```

The file format of the Snowflake code is documented [here][3].

**Note:**

* An `@` in front of the `@00` denotes that it's referring to Bank 00.
* An `:` in front of the `:00` denotes that it's referring to Label 00.
* A lack of `@` or `:` in front of a number/string denotes that it's referring to a literal.

[1]: language-reference.md
[2]: interpreter.md
[3]: file-format.md
