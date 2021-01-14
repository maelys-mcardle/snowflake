# Language Reference

Snowflake has **instructions** and **parameters**. Instructions are commands telling the interpreter 
to perform a task. Each instruction has up to two parameters. Parameters specify extra 
information the instruction needs to complete the task.

## Instructions

Below is the full instruction set supported by Snowflake. There are different types of 
values: `LITERAL`, `LABEL`, `BANK`, `TYPE`, and `DEVICE`. A value between square brackets,
such as `[LITERAL]`, indicates that this value is optional.

While the instruction will be refered to by its instruction code in the code, the 
interpreter will substitute the instruction code for its mnemonic when the code is 
displayed by the interpreter.

```
NOTE

   BANK is a positive integer preceded with a @ symbol (eg. @01).
LITERAL can be anything (text, positive integer, float)
  LABEL is a positive integer preceded with a : symbol (eg. :01).
 DEVICE is a positive integer.
   TYPE is a positive integer between 11 and 15, reflecting the TYPES instructions
```

```
BASIC

CODE  MNEMONIC  PARAMETERS       DESCRIPTION
---  ---------  --------------   -----------
00   !!!        [LITERAL]        A comment that is embedded with the code.
                                 For comments not embedded in the code, use
                                 double semi-colons (";;").
01   ###        LABEL  [LITERAL] A label: this defines where jumps can jump to.
                                 Labels are positive integers.
                                 Labels can be assigned a name with a string stored
                                 in the literal.
                                 You can only define each label once.
02              BANK    LITERAL  Assign a name to a BANK. 
                                 Banks are positive integers.
                                 Names are strings.
                                 This instruction is not required to use a bank.
                                 You can only name each bank once.
03    <<        DEVICE  BANK     Send BANK contents to a DEVICE.
                        LITERAL  Devices are positive integers.
04    >>        DEVICE  BANK     Receive DEVICE data into a BANK.
                        LITERAL  Devices are positive integers.
05     =        BANK1   BANK2    Copy BANK2 contents to BANK1.
                        LITERAL  BANK1 takes on the type of BANK2.
                                 If BANK2 is unallocated, BANK1 is deleted.
06    TO        BANK    TYPE     Converts the contents of BANK to the type set by TYPE.
                                 If BANK is unallocated, default values are used.
                                 If TYPE is `15` (array), an empty array is created.
07   TYP        BANK1   BANK2    Stores the TYPE of BANK2 into BANK1.
                        LITERAL  This type is stored as an integer.
                                 If BANK2 is unallocated, stores 0 in BANK1.
08   DEL        BANK             Deletes all data associated with BANK.
09   LEN        BANK1   BANK2    Stores the size of BANK2 into BANK1 as integer.
                        LITERAL  For string type, stores string length.
                                 For array type, stores the number of items.
                                 For other types, stores 0.
```

```
TYPES

CODE  MNEMONIC  PARAMETERS      DESCRIPTION
---  ---------  --------------  -----------
10   VAR        BANK LITERAL    Stores LITERAL in BANK. 
                                Type is inferred: depending on the 
                                literal it is stored as an integer,
                                float, or string.
11   BLN        BANK LITERAL    Stores LITERAL into BANK as a boolean.
12   INT        BANK LITERAL    Stores LITERAL into BANK as an integer.
13   FLT        BANK LITERAL    Stores LITERAL into BANK as a float.
14   STR        BANK LITERAL    Stores LITERAL into BANK as a string.
15    []        BANK            Stores an empty array into BANK.
```

```
BRANCHING

CODE  MNEMONIC  PARAMETERS      DESCRIPTION
---  ---------  --------------  -----------
20    ->        LABEL           Jumps to a LABEL.
                LITERAL         If the label does not exist, the jump is ignored.
21    ->        BANK            Jumps to the LABEL as stored in BANK.
                                If the label does not exist, the jump is ignored.
22   IF=        BANK1   BANK2   If BANK1 is equal to BANK2, 
                        LITERAL run the next instruction (often a jump), 
                                otherwise, skip the next instruction.
23   IF!        BANK1   BANK2   If BANK1 is not equal to BANK2,
                        LITERAL run the next instruction (often a jump), 
                                otherwise skip the next instruction.
24   IF>        BANK1   BANK2   If BANK1 is greater than BANK2,
                        LITERAL run the next instruction (often a jump), 
                                otherwise skip the next instruction.
25   IF<        BANK1   BANK2   If BANK1 is less than BANK2,
                        LITERAL run the next instruction (often a jump), 
                                otherwise skip the next instruction.

Note: Equality checks can be performed on all types except ARRAY.
      Greater than / lesser than comparisons are only performed on 
      INTEGER and FLOAT types.
```

```
MATH

CODE  MNEMONIC  PARAMETERS      DESCRIPTION
---  ---------  --------------  -----------
30     +        BANK1   BANK2   Add BANK2 to BANK1. Result in BANK1.
                        LITERAL
31     -        BANK1   BANK2   Subtract BANK2 from BANK1. Result in BANK1.
                        LITERAL
32     *        BANK1   BANK2   Multiply BANK2 with BANK1. Result in BANK1.
                        LITERAL
33     /        BANK1   BANK2   Divide BANK1 by BANK2. Result in BANK1.
                        LITERAL
34     %        BANK1   BANK2   Modulo of BANK1 by BANK2. Result in BANK1.
                        LITERAL
35    **        BANK1   BANK2   Power of BANK1 to BANK2. Result in BANK1.
                        LITERAL
36   SQR        BANK            Square root of BANK.

Note: These instructions are only performed on INTEGER and FLOAT types.
      All other types are ignored. The addition instruction can be performed on 
      STRING types as well; it concatenates strings together. Instruction is 
      ignored if a bank doesn't have a value.
```

```
LOGICAL 

CODE  MNEMONIC  PARAMETERS      DESCRIPTION
---  ---------  --------------  -----------
40   !          BANK            Logical NOT. Inverts the value of BANK.
41   &          BANK1   BANK2   Logical AND. Result stored in BANK1.
42   |          BANK1   BANK2   Logical OR. Result stored in BANK1.
43   ^          BANK1   BANK2   Logical XOR. Result stored in BANK1.

Note: These instructions are only performed on BOOLEAN and INTEGER types.
      All other types are ignored. Instruction is ignored if a bank
      doesn't have a value.
```

```
ARRAYS 

CODE  MNEMONIC  PARAMETERS      DESCRIPTION
---  ---------  --------------  -----------
15    []        BANK            Stores an empty array into BANK.
50   +[]        BANK1   BANK2   Moves the contents of BANK2 into a 
                        LITERAL new first item of the BANK1 array.
51   []+        BANK1   BANK2   Moves the contents of BANK2 into a 
                        LITERAL new last item of the BANK1 array.
52   -[]        BANK1   BANK2   Moves the first item of the BANK1 array
                        LITERAL into BANK2.
53   []-        BANK1   BANK2   Moves the last item of the BANK1 array
                        LITERAL into BANK2.
54   >[]        BANK1   BANK2   Moves the first item of the BANK1 array 
                        LITERAL to the index specified in BANK2.
55   []<        BANK1   BANK2   Moves the last item of the BANK1 array 
                        LITERAL to the index specified in BANK2.
56   [<]        BANK1   BANK2   Moves an item at the index specified in BANK2 
                        LITERAL to the first item of the array BANK1.
57   [>]        BANK1   BANK2   Moves an item at the index specified in BANK2 
                        LITERAL to the last item of the array BANK1.

Note: These instructions are only performed on ARRAY types.
      All other types are ignored. Instruction is ignored if the
      bank array isn't defined. Arrays are zero-indexed.
```

## Parameters

Parameters can be **banks**, **labels**, **devices**, **types** or **literals**.

### Banks

*Positive integer.*

Snowflake uses the concept of a **bank** to store a value. These values have a type, which can 
either be boolean, integer, floating point, string or array. 

Banks are refered to by a numeric identifier. The numbers must be positive, but don't have to 
follow one another, nor be sequential. There can be gaps between these numbers. Banks can also 
be given a string-based name with the `02` instruction. While the bank will be refered to by its 
numeric identifier in the code, the interpreter will substitute the bank number for a name when 
the code is displayed by the interpreter. Banks come into existence when they are refered to 
by an instruction.

### Labels

*Positive integer.*

Snowflake uses the concept of a **label** for jumping between different points in the code. 

Labels are refered to by a numeric identifier. The numbers must be positive, but don't have to 
follow one another, nor be sequential. There can be gaps between these numbers. Labels are 
defined with the `01` instruction. Labels can also be given a string-based name with the same 
instruction. While the label will be refered to by its numeric identifier in the code, the 
interpreter will substitute the label number for a name when the code is displayed by the interpreter.

### Devices

*Positive integer.*

Devices refer to hardware or a virtual device that the Snowflake interpreter can interact with. This
is how data is sent to the screen, and received from the keyboard.

While the device will be refered to by its numeric identifier in the code, the interpreter will substitute 
the device number for its mnemonic when the code is displayed by the interpreter.

```
DEVICE  MNEMONIC  DESCRIPTION 
------  --------  -----------
00      OUT       Standard output device (eg. screen)
                  Accepts any value type.
01       IN       Standard input device (eg. keyboard)
                  Stores value as string.
02      BTN       Button Press
                  This is an input device.
                  Stores value as integer.
03      RND       Random number generator.
                  As an input device: returns a random number.
                  As an output device: seeds the PRNG.
                  Input and output are both integers.
```

**The difference between `IN` and `BTN`:** `IN` stores the input to a BANK after the `ENTER` button is pressed.
This can contain multiple characters. The `BTN` stores the input immediately after a single key is pressed. 
It will return a number corresponding to the key code of the button presed.

### Types

*Positive integer.*

Types are a code used to specify the type of data stored in a Bank.

While the type will be refered to by its numeric identifier in the code, the interpreter will substitute 
the number for its mnemonic when the code is displayed by the interpreter.

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

### Literals

*String.*

Literals represent any value. They are initially taken in as a string,
and then interpreted as a variable, boolean, integer, floating point, 
or string depending on the instruction.

## Comments

There's two types of comments in Snowflake:
* There are comments that are embedded with the code, and will be kept during execution. 
  * Use instruction `00` (`!!!`) for those.
  * These comments behave like any other instruction.
* There are comments that are discarded on execution. 
  * These comments follow a double semi-colon `;;`.
  * These comments can be on their own line.
  * These comments can also be on the same line as an instruction. 

Here's an example with both types of comments:

```
00 SET AN INTEGER   ;; Program title.
12 00 42            ;; Set Bank 00 to be an integer of value 42.
```

## More on Types

### Variable

Variables automatically infer a type based on the input:

* If a whole number is entered, its stored as an integer.
* If a decimal number is entered, its stored as a float.
* If any other characters are entered, its stored as a string.

### Boolean

Boolean are stored as a `0` or a `1`.

```
VALUE   MEANING
------  -------
0       False
1       True
```

**Note**: Non-zero values are treated as true.

### Integer

Integers are 16 or 32 bit, depending on the compilation target of the interpreter.

### Float

Floats are 32-bit floating point values.

### String

Strings are in ASCII with the default interpreter implementation. Unicode is not
supported with the default interpreter implementation.

### Array

Arrays store values; these can be boolean, integers, float, string, or other arrays.
Arrays are zero-indexed and dynamically resized to fit their contents. The index of the
array is a positive integer.
