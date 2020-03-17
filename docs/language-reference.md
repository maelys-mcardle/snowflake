# Language Reference

Snowflake has instructions. Instructions are like commands telling the interpreter to perform a task.
Each instruction has up to two parameters, depending on the instruction. Parameters specify extra 
information needed to complete the task.

This documentation covers these concepts and all the supported instructions.

## Instructions

Below is the full instruction set supported by Snowflake. There are different types of 
values: `LITERAL`, `LABEL`, `BANK`, `TYPE`, and `DEVICE`. A value between square brackets,
such as `[LITERAL]`, indicates that this value is optional.

```
BASIC

CODE  MNEMONIC  PARAMETERS       DESCRIPTION
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
                                 This instruction is not required to use a bank.
                                 Re-defining a bank is undefined behaviour.
03    <<        DEVICE  BANK     Send BANK contents to a DEVICE.
                                 Devices are positive integers.
04    >>        DEVICE  BANK     Receive DEVICE data into a BANK.
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
09   LEN        BANK1   BANK2    Stores the size of BANK2 into BANK1 as integer.
                                 For string type, stores string length.
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
                                If the label does not exist, the jump is ignored.
21    ->        BANK            Jumps to the LABEL as stored in BANK.
                                If the label does not exist, the jump is ignored.
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

CODE  MNEMONIC  PARAMETERS      DESCRIPTION
---  ---------  --------------  -----------
30     +        BANK1   BANK2   Add BANK2 to BANK1. Result in BANK1.
31     -        BANK1   BANK2   Subtract BANK2 from BANK1. Result in BANK1.
32     *        BANK1   BANK2   Multiply BANK2 with BANK1. Result in BANK1.
33     /        BANK1   BANK2   Divide BANK1 by BANK2. Result in BANK1.
34     %        BANK1   BANK2   Modulo of BANK1 by BANK2. Result in BANK1.
35    **        BANK1   BANK2   Power of BANK1 to BANK2. Result in BANK1.
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
15    []        BANK            Converts BANK into an empty array.
50   +[]        BANK1   BANK2   Moves the contents of BANK2 into a 
                                new first item of the BANK1 array.
51   []+        BANK1   BANK2   Moves the contents of BANK2 into a 
                                new last item of the BANK1 array.
52   -[]        BANK1   BANK2   Moves the first item of the BANK1 array
                                into BANK2.
53   []-        BANK1   BANK2   Moves the last item of the BANK1 array
                                into BANK2.
54   >[]        BANK1   BANK2   Moves the first item of the BANK1 array 
                                to the index specified in BANK2.
55   []<        BANK1   BANK2   Moves the last item of the BANK1 array 
                                to the index specified in BANK2.
56   [<]        BANK1   BANK2   Moves an item at the index specified in BANK2 
                                to the first item of the array BANK1.
57   [>]        BANK1   BANK2   Moves an item at the index specified in BANK2 
                                to the last item of the array BANK1.

Note: These instructions are only performed on ARRAY types.
      All other types are ignored. Instruction is ignored if the
      bank array isn't defined.
```

## Parameters

Banks, Labels, Devices and Types are all positive whole numbers.

Literals can be anything.

### Banks

Snowflake uses the concept of a **Bank** to store a value. These values have a type, which can either be boolean, integer, floating point, string or array. Banks are numbered. The numbers don't have to follow one another, or be sequential. There can be gaps. Banks can also be given names. The interpreter will substitute the bank number for a name, if one is provided.

### Labels

Snowflake uses the concept of a **Label** for jumping between different points in the code. Like banks, labels are numbered. The numbers don't have to follow one another, or be sequential. There can be gaps. Labels can also be given names. The interpreter will substitute the bank number for a name, if one is provided.

### Devices

Devices refer to hardware or a virtual device that the Snowflake interpreter can interact with. This
is how data is sent to the screen, and received from the keyboard.

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

**The difference between `IN` and `BTN`:** `IN` stores the input to a BANK after the `ENTER` button is pressed. This can contain multiple characters. The `BTN` stores the input immediately after a single key is pressed. It will return a number corresponding to the key code of the button presed.

### Types

Types are a code used to specify the type of a Bank.

```
TYPES

TYPE  MNEMONIC  DESCRIPTION
---  ---------  -----------
10   VAR        Variable
11   BLN        Boolean
12   INT        Integer
13   FLT        Float
14   STR        String
15    []        Array
```

`VAR` is distinct from the other types, as values are never stored as a variable. Rather,
they are immediately inferred and stored as a `INT`, `FLT` or `STR`.

### Literals

`LITERAL` can be variable, boolean, integer, floating point, or string.

#### Variable

Variables automatically infer a type based on the input:

* If a whole number is entered, its stored as an integer.
* If a decimal number is entered, its stored as a float.
* If any other characters are entered, its stored as a string.

#### Boolean Values

Boolean are stored as a `0` or a `1`.

```
VALUE   MEANING
------  -------
0       False
1       True
```

**Note**: Any value other than zero is treated as true.

#### Integer

Integers are 16 or 32 bit numbers, depending on the compilation target of the interpreter.

#### Float

Floats are 32-bit floating point values.

#### String

Strings are ASCII strings with the default interpreter implementation. Unicode is not
supported with the default interpreter implementation.

