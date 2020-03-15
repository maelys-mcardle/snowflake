# Hello, World!

This is what a simple "hello world" program looks like in Snowflake:

```
10 01 HELLO WORLD!    ;; Store "HELLO WORLD!" in Bank 01
03 00 01              ;; Display the contents of Bank 01
```

Lines in Snowflake have the following format, where brackets indicate that
the fields are optional:

```
INSTRUCTION [PARAMETER] [PARAMETER] [;; COMMENT]
```

The parameters can be optional, depending on the instruction. So the instruction
on the first line `10` is to declare a variable. This instruction, along with all
instructions, are documented in the [reference documentation][6].

The first parameter is where the variable is stored, in this case, bank `01`. 
The second parameter is what to store in the variable, in this case, the 
string `HELLO WORLD!`. 

This is what the first line of the code above looks like when it's passed 
through the Snowflake interpreter with the `--print` flag:

```
VAR @00 HELLO WORLD!
```

`VAR` for declaring a variable; the `@00` means bank `00`; and what follows is
the string that's stored in the bank.

The second line, instruction `03` is for sending data to a device. The first
parameter defines which device to send the information to. `00` means standard
output, which is the display. The second parameter is which bank will have its
contents sent to this device. In this case, bank `01`.

This is what the first two lines of the code looks like when it's passed 
through the Snowflake interpreter with the `--print` flag:

```
VAR @00 HELLO WORLD!
 << OUT @00
```

The file format of the Snowflake code is documented [here][7].

[6]: instruction-set.md
[7]: file-format.md
[8]: project-structure.md

**Note:**

* An `@` in front of the `@00` denotes that it's referring to Bank 00.
* An `:` in front of the `:00` denotes that it's referring to Label 00.
* A lack of `@` or `:` in front of a number/string denotes that it's referring to a literal.
