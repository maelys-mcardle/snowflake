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

## Writing Snowflake Code

Snowflake code looks a bit like machine code. Most of it is written using 
digits, reflecting the limited input devices its intended to support for
programming it. Here's one program written in Snowflake which gives a random 
number between 1 and 6:

```
;; Output title.
14 00 ROLL THE DICE ;; Define string
03 00 00            ;; Output string to screen

;; Set the values.
04 03 01            ;; Store random number in Bank @01
12 02 06            ;; Store integer "06" in Bank @02

;; Provide a random number between 1 and 6.
34 01 02            ;; Bank @01 = Bank @01 % Bank @02
37 01               ;; Bank @01 = Bank @01 + 1
03 00 01            ;; Output Bank @01 to screen
```

In the example above, everything after the double semi-colon (`;;`) is
a comment and won't be executed.

To learn how to write code in Snowflake, see the [documentation][3]. 

To see other examples of code, see the [samples directory][4].

[1]: https://www.maelys.bio/
[2]: docs/interpreter.md
[3]: docs/
[4]: samples/

