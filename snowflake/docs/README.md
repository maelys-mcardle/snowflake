# Snowflake

**Snowflake** is a programming language designed for a hypothetical device with a numeric keypad for input. In this input system, typing digits is presumed to be easy, but [letters is arduous][3]. This device is also presumed to have a limited display, 20 characters wide and 4 lines tall, and to be memory-bound rather than CPU-bound.

This programming language exists somewhere between machine code and BASIC. Snowflake is [Turing-complete][1] and uses the [Polish notation][2].

[1]: https://en.wikipedia.org/wiki/Turing_completeness
[2]: https://en.wikipedia.org/wiki/Polish_notation
[3]: https://en.wikipedia.org/wiki/Multi-tap

## Reference

### Instruction Set

Below is the full instruction set supported by Snowflake. There are different types of values: `LITERAL`, `LABEL`, `BANK`, `TYPE`, and `DEVICE`. A value between square brackets, such as `[LITERAL]`, indicates that this value is optional.

```
BASIC

CODE  MNEMONIC  ARGUMENTS        DESCRIPTION
---  ---------  --------------   -----------
00   !!!        [LITERAL]        A comment.
                                 Defining a comment is optional.
01   ###        LABEL  [LITERAL] A label. 
                                 Labels are positive integers.
                                 Names are optional. They are strings when defined.
                                 Labels and their names should be unique.
                                 Re-defining a label is undefined behaviour.
02              BANK    LITERAL  Assign a name to a BANK. 
                                 Banks are positive integers.
                                 Names are strings.
                                 Re-defining a bank is undefined behaviour.
03    <<        DEVICE  BANK     Ouput to LCD / Printer / etc, as defined by DEVICE.
                                 Each invocation of OUT is on its own new line.
                                 Devices are positive integers.
04    >>        DEVICE  BANK     Input from Buttons / etc, as defined by DEVICE.
                                 The value is stored in the BANK after the OK key is pressed.
                                 Devices are positive integers.
05     =        BANK1   BANK2    Copy BANK2 contents to BANK1.
                                 BANK1 takes on the type of BANK2.
                                 If BANK2 is unallocated, BANK1 is deleted.
06    TO        TYPE    BANK     Converts BANK to the type set by TYPE.
                                 This is equivalent to types instructions below,
                                 where the LITERAL is instead the value in the BANK.
                                 If BANK is unallocated, default values are used.
07   TYP        BANK1   BANK2    Stores the TYPE of BANK2 into BANK1.
                                 This type is stored as an integer.
                                 If BANK2 is unallocated, stores 0 in BANK1.
08   DEL        BANK             Deletes all data associated with BANK.

```

```
TYPES

CODE  MNEMONIC  ARGUMENTS       DESCRIPTION
---  ---------  --------------  -----------
10   VAR        BANK LITERAL    Stores LITERAL in BANK. Type is inferred.
11   BLN        BANK LITERAL    Stores LITERAL into BANK as a boolean.
12   INT        BANK LITERAL    Stores LITERAL into BANK as an integer.
13   FLT        BANK LITERAL    Stores LITERAL into BANK as a float.
14   STR        BANK LITERAL    Stores LITERAL into BANK as a string.
15    []        BANK            Stores an empty array into BANK.
```

```
BRANCHING

CODE  MNEMONIC  ARGUMENTS       DESCRIPTION
---  ---------  --------------  -----------
20    ->        LABEL           Jumps to a LABEL.
21    ->        BANK            Jumps to the LABEL as stored in BANK. 
22   IF=        BANK1   BANK2   If BANK1 is equal to BANK2, 
                                run the next instruction (often a jump), 
                                otherwise, skip the next instruction.
23   IF!        BANK1   BANK2   If BANK1 is not equal to BANK2,
                                run the next instruction (often a jump), 
                                otherwise skip the next instruction.
24   IF>        BANK1   BANK2   If BANK1 is greater than BANK2,
                                run the next instruction (often a jump), 
                                otherwise skip the next instruction.
                                This instruction is only performed on
                                integer and float types. The next
                                instruction is skipped for other types.
25   IF<        BANK1   BANK2   If BANK1 is less than BANK2,
                                run the next instruction (often a jump), 
                                otherwise skip the next instruction.
                                This instruction is only performed on
                                integer and float types. The next
                                instruction is skipped for other types.
```

```
MATH

CODE  MNEMONIC  ARGUMENTS       DESCRIPTION
---  ---------  --------------  -----------
30   +          BANK1   BANK2   Add BANK2 to BANK1.
31   -          BANK1   BANK2   Subtract BANK2 from BANK1.
32   *          BANK1   BANK2   Multiply BANK2 with BANK1. Store in BANK1.
33   /          BANK1   BANK2   Divide BANK1 by BANK2, store result in BANK1.
34   %          BANK1   BANK2   Modulo of BANK1 by BANK2, store result in BANK1.
35   **         BANK1   BANK2   BANK1 to the power of BANK2, stored in BANK1.

Note: These instructions are only performed on INTEGER and FLOAT types.
      All other types are ignored.
```

```
LOGICAL 

CODE  MNEMONIC  ARGUMENTS       DESCRIPTION
---  ---------  --------------  -----------
40   !          BANK            Logical NOT. Inverts the value of BANK.
41   &          BANK1   BANK2   Logical AND. Result stored in BANK1.
42   |          BANK1   BANK2   Logical OR. Result stored in BANK1.
43   ^          BANK1   BANK2   Logical XOR. Result stored in BANK1.

Note: These instructions are only performed on BOOLEAN and INTEGER types.
      All other types are ignored.
```

```
ARRAYS 

CODE  MNEMONIC  ARGUMENTS       DESCRIPTION
---  ---------  --------------  -----------
15    []        BANK            Converts BANK into an empty array.
50   [#]        BANK1   BANK2   Stores the length of the BANK1 array into BANK2.
                                BANK2 becomes an INT type.
51   +[]        BANK1   BANK2   Appends the contents of BANK2 to the start of the BANK1 array.
52   []+        BANK1   BANK2   Appends the contents of BANK2 to the end of the BANK1 array.
53   ?[]        BANK1   BANK2   Copies the first item of the BANK1 array into BANK2.
                                BANK2 becomes the type of the first item in the BANK1 array.
54   []?        BANK1   BANK2   Copies the last item of the BANK1 array into BANK2.
                                BANK2 becomes the type of the last item in the BANK1 array.
55   -[]        BANK            Removes the first item of the BANK array.
56   []-        BANK            Removes the last item of the BANK array.
57   [>]        BANK1   BANK2   Moves the first item of the BANK1 array to the index specified in BANK2.
58   [<]        BANK1   BANK2   Moves an item at the index specified in BANK2 to the first item of the array BANK1.

Note: These instructions are only performed on ARRAY types.
      All other types are ignored.
```

### Banks

Snowflake uses the concept of a **Bank** to store a value. These values have a type, which can either be boolean, integer, floating point, or string. Banks are numbered. The numbers don't have to follow one another, or be sequential. There can be gaps. Banks can also be given names. The interpreter will substitute the bank number for a name, if one is provided.

When a value is taken from a literal or another bank into a bank, the destination bank determines the type. So if a string is added to an integer, and the value is to be stored in a bank that's been allocated to an integer, then the result will be an integer. This process is refered to as [type coersion][3].

[3]: https://developer.mozilla.org/en-US/docs/Glossary/Type_coercion

### Labels

Snowflake uses the concept of a **Label** for jumping between different points in the code. Like banks, labels are numbered. The numbers don't have to follow one another, or be sequential. There can be gaps. Labels can also be given names. The interpreter will substitute the bank number for a name, if one is provided.

### Literals

`LITERAL` can be boolean, integer, floating point, or string.

If literals are inferred, it's according to the following rules:
* If 0-9 is entered, its stored as an INTEGER.
* If 0-9 with a . is entered, its stored as a FLOAT.
* If any other characters are entered, its stored as a STRING.

### Boolean Values

```
VALUE   MEANING
------  -------
0       False
1       True
```

**Note**: Any value other than zero is treated as true.

### Devices

```
DEVICE  MNEMONIC  DESCRIPTION 
------  --------  -----------
00      OUT       Default output device (eg. screen)
                  This is an output device.
                  Accepts any value type.
01       IN       Default input device (eg. keyboard)
                  This is an input device.
                  Stores value as string.
02      PRT       Thermal Printer
                  This is an output device.
                  Accepts any value type.
03      BTN       Button Press
                  This is an input device.
                  Stores value as integer.
```

**The difference between `IN` and `BTN`:** `IN` stores the input to a BANK after the `ENTER` button is pressed. This can contain multiple characters. The `BTN` stores the input immediately after a single key is pressed. It will return a number corresponding to the key code of the button presed. When this instruction is used, only the `RUN/STOP` button will stop execution.

### Types

```
TYPES

TYPE  MNEMONIC  DESCRIPTION
---  ---------  -----------
11   BLN        Boolean
12   INT        Integer
13   FLT        Float
14   STR        String
15    []        Array
```

## Sample Code

### Hello World

This program outputs "Hello World!" to the LCD:

```
10 00 HELLO WORLD!    ;; Store "HELLO WORLD!" to Bank 00
03 00 00              ;; Output the contents of Bank 00 to the LCD
```

The interpreter would replace the above with mnemonics as the user typed:

```
VAR @00 HELLO WORLD!    ;; Store "HELLO WORLD!" to Bank 00
 << OUT @00             ;; Output the contents of Bank 00 to the LCD
```

**Note:**

* An `@` in front of the `@00` denotes that it's referring to Bank 00.
* An `:` in front of the `:00` denotes that it's referring to Label 00.
* A lack of `@` or `:` in front of a number/string denotes that it's referring to a literal.
