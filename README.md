# Snowflake

Snowflake is an interpreted programming language made for microcontrollers. 
The language is like a [human-writeable byte code][1].

This repository contains the following:

* The Snowflake interpreter. See the [interpreter][1] documentation.
* Documentation on how to write Snowflake programs. See the [docs][2] directory. 
* Example Snowflake code. See the [samples][3] directory.

[1]: docs/interpreter.md
[2]: docs/
[3]: samples/

## Author

Snowflake was developed for fun by [Maëlys McArdle][3].

[4]: https://www.maelys.bio/

## Interpreter

To get and compile the Snowflake interpreter, run the following:

```
# Clone the repository
git clone git@github.com:maelys-mcardle/snowflake.git

# Switch into the repository directory
cd snowflake

# Compile the interpreter
make
```

Then test by running a sample file:

```
./snowflake --run samples/hello-world.sn
```
