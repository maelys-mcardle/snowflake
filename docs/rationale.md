# Rationale: Why Snowflake

**Short answer:** I made Snowflake for fun. If you're looking at a language
to adopt for your microcontroller project, I'd recommend you take
a look at [MicroPython][1] instead.

**Long answer:** This project is an offshoot of a project to build
a calculator-sized device that you can program with using only a numeric
keypad. Think [KIM-1][2] but with a 20 character alphanumeric display.

Machine code was a natural fit for this limited device, but I wanted to 
take the tedium out and leverage the significant CPU and memory of contemporary
microcontrollers by creating a higher-level programming language. Out came
Snowflake.

Snowflake has high-level types such as strings and arrays, and can do a 
"hello, world!" in two lines of code. When compiled for size on Linux the 
interpreter consumes about 60 kilobytes of storage and consumes about 80 
kilobytes of memory.

Really though, this was an excuse to have fun and design a programming language
for a device with interesting limitations.

[1]: https://micropython.org/
[2]: https://en.wikipedia.org/wiki/KIM-1
