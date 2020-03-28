# Rationale: Why Snowflake

If you're stumbling upon this repository and wondering whether to adopt
Snowflake for your project, you probably shouldn't. I'd recommend you take
a look at [MicroPython][1].

This project was created initially as an offshoot of a project to build
a calculator-sized device that you could program with using only a numpad.
Machine code is a natural fit for this, such as with the [KIM-1][2], but I
wanted to take the tedium out and leverage the underlying microcontroller's
significant CPU and memory advantage by creating a higher-level programming
language that could be programmed with a numpad. Plus I wanted to have fun
creating a new programming language. Out came Snowflake.

Snowflake supports input/output devices, has high-level types such as strings
and arrays, and can do a "hello, world!" in two lines of code. When compiled
for size on Linux the interpreter is about 50 kilobytes. Complex programs in
Snowflake take hundreds of bytes of memory.

But more importantly, it's been fun to out together.

[1]: https://micropython.org/
[2]: https://en.wikipedia.org/wiki/KIM-1
