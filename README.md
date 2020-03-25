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

Snowflake code looks a bit like machine code. There are instructions, devices,
banks and labels and these are all written using digits. Here's one program
written in Snowflake which gives a random number between 1 and 6:

```
;; Output title.
14 00 ROLL THE DICE ;;
03 00 00            ;; Output "ROLL THE DICE"

;; Set the values.
04 03 01            ;; BANK @01 = RANDOM_NUMBER()
12 02 06            ;; BANK @02 = 6
12 03 01            ;; BANK @03 = 1

;; Provide a random number between 1 and 6.
34 01 02            ;; BANK @01 = (BANK @01) % 6
30 01 03            ;; BANK @01 = (BANK @01) + 1
03 00 01            ;; Output BANK @01
```

To learn how to write code in Snowflake, see the [documentation][3].
To other examples of code, see the [samples directory][4].

[1]: https://www.maelys.bio/
[2]: docs/interpreter.md
[3]: docs/
[4]: samples/

