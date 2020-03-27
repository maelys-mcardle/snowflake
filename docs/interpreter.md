# Snowflake Interpreter

The interpreter is used to execute Snowflake code as well as print 
out a human-readable version. Before the interpreter can be used,
it must first be **compiled**.

## Prerequisites

Compilation of the interpreter requires [make][1], a C compiler 
with [c11][2] support, as well as [glibc][3]. Downloading the
interpreter requires [git][4].

On Ubuntu, run the following to install these requirements:

```sh
sudo apt install build-essential git
```

On Fedora, run the following to install these requirements:

```sh
dnf install @development-tools git
```

## Download Repository

To download this repository containing the interpreter, run the
following command. It will create the directory `snowflake` which
will contain all this code:

```sh
git clone git@github.com:maelys-mcardle/snowflake.git
```

Then switch into the `snowflake` directory:

```sh
cd snowflake
```

## Compile Interpreter

To compile the interpreter, run the command from the project root:

```sh
make
```

To compile with debug symbols run the command:

```sh
make debug
```

## Run Snowflake Programs

To execute a Snowflake program, use the `--run` or `-r` option:

```sh
./snowflake --run samples/hello-world.sn
```

The interpreter will run the code:

```
Hello, World!
```

## Display Program Code

Snowflake programs are largely written using digits. To see the human-readable version
with mnemonics and variable names substituted, use the `--print` or `-p` option:

```sh
./snowflake --print samples/hello-world.sn
```

For the `hello-world.sn` example above, the interpreter will produce 
the following:

```
VAR @00 Hello, World!
 << OUT @00
```

## Debug Programs

If a Snowflake program isn't parsed or executed as expected, use
the `--debug` or `-d` option. This will give in-depth information 
about what the interpreter is doing at each step. The debug build of 
the interpreter is not required.

```sh
./snowflake --print --run --debug your-snowflake-program.sn
```

## Remove Compilation Files

To delete files created during the compilation of the 
interpreter, run the command:

```sh
make clean
```

[1]: https://en.wikipedia.org/wiki/Make_(software)
[2]: https://en.wikipedia.org/wiki/C11_(C_standard_revision)
[3]: https://en.wikipedia.org/wiki/GNU_C_Library
[4]: https://git-scm.com/
