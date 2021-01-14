# Hello, World!

This is what "hello world" looks like in Snowflake:

```
<< OUT Hello, World!  ;; Display "Hello, World!"
```

## Breaking it down

### Instructions

Each line of Snowflake code is an instruction. These lines in Snowflake have the following format:

```
INSTRUCTION PARAMETER PARAMETER
```

In this case, the instructions take two parameters. But other instructions
can take zero or one parameter, depending on the instruction. All instructions
and their parameters are documented in the [reference documentation][1]. 
Comments are optional and follow a double semi-colon (`;;`),

```
<< OUT Hello, World!
```

* The `<<` is the output instruction. It's for sending data to a device
  (see [reference documentation][1]). It takes two parameters.
* The first parameter is what to output to. `OUT` is the standard output 
  device, which is the most common way of displaying data back to the user.
* The second parameter can be a literal or a bank. A bank is a place in memory to 
  store things. This isn't that. This is a literal, which is a value. In this case,
  the text "Hello, World!".

[1]: language-reference.md
[2]: interpreter.md
[3]: file-format.md
