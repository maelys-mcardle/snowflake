# Snowflake

Snowflake is an interpreted programming language for microcontrollers.

## Author

[Maëlys McArdle][1].

## Getting Started

To get and compile the Snowflake interpreter, run the following:

```sh
# Clone the repository
git clone git@github.com:maelys-mcardle/snowflake.git

# Switch into the repository directory
cd snowflake

# Compile the interpreter
make
```

Then test by running the `hello-world.sn` program. It should display
`Hello, World!` on-screen:

```sh
./snowflake --run samples/hello-world.sn
```

More information is found in the [interpreter documentation][2].

To learn how to write code in Snowflake, see the [documentation][3]. 

To see other examples of code, see the [samples directory][4].

[1]: https://www.maelys.bio/
[2]: docs/interpreter.md
[3]: docs/
[4]: samples/

