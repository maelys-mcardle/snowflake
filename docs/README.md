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

## Documentation

The documentation is split into the following files:

* Documentation for compiling and using the interpreter is in [interpreter.md][8].
* The complete reference to the Snowflake programming language is found in [language-reference.md][6].
* A first example file is analyzed in [hello-world.md][7].
* The snowflake file format is covered in [file-format.md][10].
* How this repository is laid out is covered in [project-structure.md][9].

[6]: language-reference.md
[7]: hello-world.md
[8]: interpreter.md
[9]: project-structure.md
[10]: file-format.md
