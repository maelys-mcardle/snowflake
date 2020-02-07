# High Level Assembly
## Rererence

### Literals

`LITERALS` can be integers, floating points, strings.

These are then loaded into a `BANK`.

### Instructions

```
CODE  MNEMONIC  ARGUMENTS       DESCRIPTION
---  ---------  --------------  -----------
00   #          LITERAL         Label or code comment.
01   NAME       BANK    LITERAL Assign a name to a BANK. This is then substituted by the interpreter like the mnemonics.
02   OUT        DEVICE  BANK    Ouput to LCD / Printer / etc, as defined by DEVICE.
03   IN         DEVICE  BANK    Input from Buttons / etc, as defined by DEVICE.
04   STO        BANK    LITERAL Store LITERAL in BANK.
05   MOV        BANK1   BANK2   Copy BANK1 contents to BANK2.
06   JMP        LITERAL         Jumps to a LINE NUMBER or LABEL defined in the LITERAL.
10   IFEQ       BANK1   BANK2   If BANK1 is equal to BANK2, run the next instruction (often a JMP), otherwise go to the instruction after.
11   IFGT       BANK1   BANK2   If BANK1 is greater than BANK2, run the next instruction (often a JMP), otherwise go to the instruction after
20   ADD        BANK1   BANK2   Add BANK1 to BANK2, store result in BANK2.
21   SUB        BANK1   BANK2   Subtract BANK2 from BANK1, store result in BANK2.
22   MUL        BANK1   BANK2   Multiply BANK1 with BANK2, store result in BANK2.
23   DIV        BANK1   BANK2   Divide BANK2 by BANK1, store result in BANK2.
24   FLR        BANK            Converts BANK into an INT, gets the floor of the value.
```

### Devices

```
DEVICE  MNEMONIC  DESCRIPTION 
------  --------  -----------
00      LCD       LCD Display
01      BTN       Buttons
02      PRNT      Thermal Printer
```
