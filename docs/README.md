# Snowflake

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

## Overview

This is what a simple "hello world" program looks like in Snowflake:

```
10 00 HELLO WORLD!    ;; Store "HELLO WORLD!" in Bank 00
03 00 00              ;; Display the contents of Bank 00
```

At first glance, this can seem terrifying. It doesn't look to mean anything!
This is what the code above looks like when it's passed through the Snowflake
interpreter with the `--print` flag:

```
VAR @00 HELLO WORLD!
 << OUT @00
```

A little better, but still confusing. Snowflake uses the notion of banks to store
information. A bank can store a boolean, integer, float, string or array. These
banks are numbered. They don't have to be sequential. So in this case, in the first line,
`HELLO WORLD!` is stored as a `VAR` (meaning variable where the type is determined 
automatically) in bank `@00`. `VAR` is instruction `10`.

The second line, instruction `03` is translated as `<<` meaning "send to device". 
The contents of bank `@00` are being send to device `00`, which is the standard
output. The display. This is translated as `OUT`.

All these instructions are documented in the [instruction set reference documentation][6].
The file format of the Snowflake code is also documented [here][7].

[6]: instruction-set.md
[7]: file-format.md
[8]: project-structure.md

**Note:**

* An `@` in front of the `@00` denotes that it's referring to Bank 00.
* An `:` in front of the `:00` denotes that it's referring to Label 00.
* A lack of `@` or `:` in front of a number/string denotes that it's referring to a literal.
