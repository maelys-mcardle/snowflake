# High Level Assembly

**High Level Assembly** is a language designed for the microprocessor trainer, to make coding a little easier. It is designed for a system that has a 20 character length display with a 4 x 4 button matrix for input. In this input system, typing numbers is easy, but letters is presumed to be arduous.

## Reference

### Instruction Set

```
BASIC I/O

CODE  MNEMONIC  ARGUMENTS       DESCRIPTION
---  ---------  --------------  -----------
00   ###        LABEL           A numeric or symbolic label. 
                                Can also act as a code comment.
00   ###        LABEL   LITERAL Assign a name to a LABEL.
01              BANK    LITERAL Assign a name to a BANK.
02    <<        DEVICE  BANK    Ouput to LCD / Printer / etc, as defined by DEVICE.
                                Each invocation of OUT is on its own new line.
03    >>        DEVICE  BANK    Input from Buttons / etc, as defined by DEVICE.
                                The value is stored in the BANK after the ENTER key is pressed.             
04     =        BANK1   BANK2   Copy BANK2 contents to BANK1.
05   DEL        BANK            Deletes all data associated with BANK.
06   TYP        BANK1   BANK2   Stores the TYPE of BANK2 into BANK1. Corresponds to codes 11-15 below.
```

```
TYPES

CODE  MNEMONIC  ARGUMENTS       DESCRIPTION
---  ---------  --------------  -----------
10   VAR        BANK            Converts BANK into the type that's inferred.
11   BLN        BANK            Converts BANK into a boolean.
12   INT        BANK            Converts BANK into an integer.
13   FLT        BANK            Converts BANK into a float.
14   STR        BANK            Converts BANK into a string.
15   ARR        BANK            Converts BANK into an empty array.

CODE  MNEMONIC  ARGUMENTS       DESCRIPTION
---  ---------  --------------  -----------
10   VAR        BANK LITERAL    Stores LITERAL in BANK. Type is inferred.
11   BLN        BANK LITERAL    Stores LITERAL into BANK as boolean.
12   INT        BANK LITERAL    Stores LITERAL into BANK as integer.
13   FLT        BANK LITERAL    Stores LITERAL into BANK as float.
14   STR        BANK LITERAL    Stores LITERAL into BANK as string.
```

```
BRANCHING

CODE  MNEMONIC  ARGUMENTS       DESCRIPTION
---  ---------  --------------  -----------
20    ->        LABEL           Jumps to a LABEL.
21   IF=        BANK1   BANK2   If BANK1 is equal to BANK2, 
                                run the next instruction (often a jump), 
                                otherwise, skip the next instruction.
22   IF!        BANK1   BANK2   If BANK1 is not equal to BANK2,
                                run the next instruction (often a jump), 
                                otherwise skip the next instruction.
23   IF>        BANK1   BANK2   If BANK1 is greater than BANK2,
                                run the next instruction (often a jump), 
                                otherwise skip the next instruction.
24   IF<        BANK1   BANK2   If BANK1 is less than BANK2,
                                run the next instruction (often a jump), 
                                otherwise skip the next instruction.
```

```
MATH 

CODE  MNEMONIC  ARGUMENTS       DESCRIPTION
---  ---------  --------------  -----------
30   +          BANK1   BANK2   Add BANK2 to BANK1.
31   -          BANK1   BANK2   Subtract BANK2 from BANK1.
32   *          BANK1   BANK2   Multiply BANK2 with BANK1. Store in BANK1.
33   /          BANK1   BANK2   Divide BANK1 by BANK2, store result in BANK1.
34   **         BANK1   BANK2   BANK1 to the power of BANK2, stored in BANK1.
```

```
LOGICAL 

CODE  MNEMONIC  ARGUMENTS       DESCRIPTION
---  ---------  --------------  -----------
40   !          BANK            Logical NOT. Inverts the value of BANK.
41   &          BANK1   BANK2   Logical AND. Result stored in BANK1.
42   |          BANK1   BANK2   Logical OR. Result stored in BANK1.
43   ^          BANK1   BANK2   Logical XOR. Result stored in BANK1.
```

```
ARRAYS 

CODE  MNEMONIC  ARGUMENTS       DESCRIPTION
---  ---------  --------------  -----------
50   +[]        BANK1   BANK2   Appends the contents of BANK2 to the start of the BANK1 array.
51   []+        BANK1   BANK2   Appends the contents of BANK2 to the end of the BANK1 array.
52   ?[]        BANK1   BANK2   Reads the first item of the BANK2 array and stores it into BANK1.
53   []?        BANK1   BANK2   Reads the last item of the BANK2 array and stores it into BANK1.
54   -[]        BANK1   BANK2   Removes the item at the start of the BANK2 array and stores it into BANK1.
55   []-        BANK1   BANK2   Removes the item at the end of the BANK2 array and stores it into BANK1.
56   [>]        BANK1   BANK2   Moves the first item of the BANK1 array to the index specified in BANK2.
57   [<]        BANK1   BANK2   Moves an item at the index specified in BANK2 to the first item of the array of BANK1.
58   [-]        BANK1   BANK2   Deletes the item at the index specified in BANK2 from the BANK1 array.
59   [?]        BANK1   BANK2   Stores the length of the BANK2 array into BANK1.
```

### Banks and Labels

It uses the concept of a **Bank** to store a value. These values have a type, which can either be boolean, integer, floating point, or string. Banks are numbered. The numbers don't have to follow one another, or be sequential. There can be gaps. Banks can also be given names. The interpreter will substitute the bank number for a name, if one is provided.

It uses the concept of a **Label** for jumping between different points in the code. Labels can be any type, but are usually an integer. These can also be given names. The interpreter will substitute the label for a name, if one is provided. The `20` instruction (mnemonic: `->`) is used to point to one of these labels; making the following instruction executed by the interpreter the one at that label. 

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

### Devices

```
DEVICE  MNEMONIC  DESCRIPTION 
------  --------  -----------
00      LCD       LCD Display
01      BTN       Buttons
02      PRT       Thermal Printer
```

## Sample Code

### Hello World

This program outputs "Hello World!" to the LCD:

```
10 00 HELLO WORLD!    ;; Store "HELLO WORLD!" to Bank 00
02 00 00              ;; Output the contents of Bank 00 to the LCD
```

The interpreter would replace the above with mnemonics as the user typed:

```
VAR @00 HELLO WORLD!    ;; Store "HELLO WORLD!" to Bank 00
 << LCD @00             ;; Output the contents of Bank 00 to the LCD
```

**Note:**

* An `@` in front of the `@00` denotes that it's referring to Bank 00.
* An `:` in front of the `:00` denotes that it's referring to Label 00.
* A lack of `@` or `:` in front of a number/string denotes that it's referring to a literal.

### Add Two Numbers

Here's a basic program that adds two numbers, as entered by the user:

```
10 00 ENTER NUMBER ;; Store string "ENTER NUMBER" in Bank 00
02 00 00           ;; Output the contents of Bank 00 to the LCD ("ENTER NUMBER")
03 01 01           ;; Store the button presses to Bank 01
02 00 00           ;; Output the contents of Bank 00 to the LCD ("ENTER NUMBER")
03 01 02           ;; Store the button presses to Bank 02
30 01 02           ;; Add Bank 02 to Bank 01
02 00 01           ;; Output the contents of Bank 01 (the sum of the addition)
```

The interpreter would replace the above with mnemonics as the user typed:

```
VAR @00 ENTER NUMBER  ;; Store string "ENTER NUMBER" in Bank 00
 << LCD @00           ;; Output the contents of Bank 00 to the LCD ("ENTER NUMBER")
 >> BTN @01           ;; Store the button presses to Bank 01
 << LCD @00           ;; Output the contents of Bank 00 to the LCD ("ENTER NUMBER")
 >> BTN @02           ;; Store the button presses to Bank 02
  + @01 @02           ;; Add Bank 02 to Bank 01
 << LCD @01           ;; Output the contents of Bank 01 (the sum of the addition)
```

### Add Two Numbers (with named banks)

Banks can also be given names, for readability:

```
00 ADD TWO NUMBERS  ;; Comment describing program
01 00 MSG           ;; Name Bank 00 "MSG"
01 01 A             ;; Name Bank 01 "A"
01 02 B             ;; Name Bank 02 "B"
10 00 ENTER NUMBER  ;; Store string "ENTER NUMBER" in MSG
02 00 00            ;; Output the contents of MSG to the LCD ("ENTER NUMBER")
03 01 01            ;; Store the button presses to A
02 00 00            ;; Output the contents of Bank 00 to the LCD ("ENTER NUMBER")
03 01 02            ;; Store the button presses to B
30 01 02            ;; Add B to A
02 00 01            ;; Output the contents of A (the sum of the addition)
```

The interpreter would replace the above with mnemonics as the user typed:

```
### ADD TWO NUMBERS    ;; Comment describing program
    @00 MSG            ;; Name Bank 00 "MSG"
    @01 A              ;; Name Bank 01 "A"
    @02 B              ;; Name Bank 02 "B"
VAR MSG ENTER NUMBER   ;; Store string "ENTER NUMBER" in MSG
 << LCD MSG            ;; Output the contents of Bank 00 to the LCD ("ENTER NUMBER")
 >> BTN A              ;; Store the button presses to Bank 01
 << LCD MSG            ;; Output the contents of Bank 00 to the LCD ("ENTER NUMBER")
 >> BTN B              ;; Store the button presses to Bank 02
  + A B                ;; Add Bank 02 to Bank 01
 << LCD A              ;; Output the contents of Bank 01 (the sum of the addition)
```

### Are you an Adult

This program asks for your age, then tells you if you're an adult or a minor.

```
00 ARE YOU AN ADULT ;; Comment describing program.
01 00 MSG           ;; Name Bank 00 "MSG"
01 01 ADULT         ;; Name Bank 01 "ADULT"
01 02 AGE           ;; Name Bank 02 "AGE"
14 00 HOW OLD ARE YOU ;; Store "HOW OLD ARE YOU" in Bank 01 00 MSG
12 01 18            ;; Store 18 (age of adulthood) in Bank 01  
02 00 00            ;; Display the message "HOW OLD ARE YOU"
03 01 02            ;; Store the button input in Bank 02 (your age)
24 02 01            ;; If Bank 02 (your age) is less than Bank 01 (age of adulthood)
20 01               ;; ...Jump to label 01.
20 00               ;; ...Otherwise jump to label 00.
00 00 IS ADULT      ;; Label 00 (for adults)
14 00 YOU ARE ADULT ;; Store "YOU ARE ADULT" in Bank 00
20 02               ;; Jump to label 02 (end).
00 01 IS MINOR      ;; Label 01 (for minors)
14 00 YOU ARE MINOR ;; Store "YOU ARE MINOR" in Bank 00
00 02 END           ;; Label 02 (end)
02 00 00            ;; Display the message in Bank 00 ("YOU ARE ADULT" or "YOU ARE MINOR")
```

The interpreter would replace the above with mnemonics as the user typed:

```
### ARE YOU AN ADULT    ;; Comment describing program.
    @00 MSG             ;; Name Bank 00 "MSG"
    @01 ADULT           ;; Name Bank 01 "ADULT"
    @02 AGE             ;; Name Bank 02 "AGE"
STR MSG HOW OLD ARE YOU ;; Store "HOW OLD ARE YOU" in Bank 00
INT ADULT 18            ;; Store 18 (age of adulthood) in Bank 01  
 << LCD MSG             ;; Display the message "HOW OLD ARE YOU"
 >> BTN AGE             ;; Store the button input in Bank 02 (your age)
IF< AGE ADULT           ;; If Bank 02 (your age) is less than Bank 01 (age of adulthood)
 -> IS ADULT            ;; ...Jump to label 01.
 -> IS MINOR            ;; ...Otherwise jump to label 00.
### IS ADULT            ;; Label 00 (for adults)
STR MSG YOU ARE ADULT   ;; Store "YOU ARE ADULT" in Bank 00
 -> END                 ;; Jump to label 02 (end).
### IS MINOR            ;; Label 01 (for minors)
STR MSG YOU ARE MINOR   ;; Store "YOU ARE MINOR" in Bank 00
### END                 ;; Label 02 (end)
 << LCD MSG             ;; Display the message in Bank 00 ("YOU ARE ADULT" or "YOU ARE MINOR")
```

### Fibonacci Sequence

The following calculates the Fibonacci Sequence up to a user-defined number.

```
03 01 00  ;; User enters MAX. Stored in Bank 00.
12 01 01  ;; CURRENT NUMBER (Bank 01) is set to 1.
12 02 01  ;; LAST NUMBER (Bank 02) is set to 1.
00 00     ;; Start of loop
04 03 01  ;; SUM = CURRENT NUMBER
30 03 02  ;; SUM = SUM + LAST NUMBER
02 00 03  ;; Output value of SUM
23 03 00  ;; If SUM > MAX
20 01     ;; ...go to end.
04 02 01  ;; CURRENT NUMBER becomes LAST NUMBER
04 03 02  ;; SUM becomes CURRENT NUMBER
20 00     ;; Start loop over.
00 01     ;; End
```

The interpreter would replace the above with mnemonics as the user typed:

```
 >> BTN @00  ;; User enters MAX. Stored in Bank 00.
INT @01 01   ;; CURRENT NUMBER (Bank 01) is set to 1.
INT @02 01   ;; LAST NUMBER (Bank 02) is set to 1.
### :00      ;; Start of loop
  = @03 @01  ;; SUM = CURRENT NUMBER
  + @03 @02  ;; SUM = SUM + LAST NUMBER
 << LCD @03  ;; Output value of SUM
IF> @03 @00  ;; If SUM > MAX
 -> :01      ;; ...go to end.
  = @02 @01  ;; CURRENT NUMBER becomes LAST NUMBER
  = @03 @02  ;; SUM becomes CURRENT NUMBER
 -> :00      ;; Start loop over.
### :01      ;; End
```

This code is a little confusing to look at. Naming banks and labels would bring clarity:

```
01 00 MAX     ;; Name Bank 00 "MAX".
01 01 CURRENT ;; Name Bank 01 "CURRENT"
01 02 LAST    ;; Name Bank 02 "LAST"
01 03 SUM     ;; Name Bank 03 "SUM"
03 01 00      ;; User enters MAX. Stored in Bank 00.
12 01 01      ;; CURRENT NUMBER (Bank 01) is set to 1.
12 02 01      ;; LAST NUMBER (Bank 02) is set to 1.
00 00 START   ;; Start of loop
04 03 01      ;; SUM = CURRENT NUMBER
30 03 02      ;; SUM = SUM + LAST NUMBER
02 00 03      ;; Output value of SUM
23 03 00      ;; If SUM > MAX
20 01         ;; ...go to end.
04 02 01      ;; ...otherwise CURRENT NUMBER becomes LAST NUMBER
04 03 02      ;; SUM becomes CURRENT NUMBER
20 00         ;; Start loop over.
00 01 END     ;; End
```

...which would produce the following:

```
    @00 MAX             ;; Name Bank 00 "MAX".
    @01 CURRENT         ;; Name Bank 01 "CURRENT"
    @02 LAST            ;; Name Bank 02 "LAST"
    @03 SUM             ;; Name Bank 03 "SUM"
 >> BTN MAX             ;; User enters MAX. Stored in Bank 00.
INT CURRENT 01          ;; CURRENT NUMBER (Bank 01) is set to 1.
INT LAST 01             ;; LAST NUMBER (Bank 02) is set to 1.
### START               ;; Start of loop
  = SUM CURRENT         ;; SUM = CURRENT NUMBER
  + SUM LAST            ;; SUM = SUM + LAST NUMBER
 << LCD SUM             ;; Output value of SUM
IF> SUM MAX             ;; If SUM > MAX
 -> END                 ;; ...go to end.
  = LAST CURRENT        ;; ...otherwise CURRENT NUMBER becomes LAST NUMBER
  = CURRENT SUM         ;; SUM becomes CURRENT NUMBER
 -> START               ;; Start loop over.
### END                 ;; End
```
