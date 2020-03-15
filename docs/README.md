# Snowflake Language

**Snowflake** is a programming language made designed with microcontrollers as both the editing 
and execution environment. It is designed for this hypothetical device:

* The target device is memory-bound rather than CPU-bound.
* Numeric keypad as the input device including [for typing letters][1]
* The output is 20 characters wide.

Conceptualize a device that's a mish-mash of a [KIM-1][2] and a 1980's pocket computer like 
the [Sharp PC-1500][3]. This resulting language is like human-writeable bytecode.
Snowflake is [Turing-complete][4] and uses the [Polish notation][5].

[1]: https://en.wikipedia.org/wiki/E.161
[2]: https://en.wikipedia.org/wiki/KIM-1
[3]: https://en.wikipedia.org/wiki/Sharp_PC-1500
[4]: https://en.wikipedia.org/wiki/Turing_completeness
[5]: https://en.wikipedia.org/wiki/Polish_notation

## Hello, World!

This is what a simple "hello world" program looks like in Snowflake:

```
10 01 HELLO WORLD!    ;; Store "HELLO WORLD!" in Bank 01
03 00 01              ;; Display the contents of Bank 01
```

Lines in Snowflake have the following format:

```
INSTRUCTION [PARAMETER] [PARAMETER]
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
