# Add Two Numbers

Here's a basic program that adds two numbers, as entered by the user:

```
10 00 ENTER NUMBER ;; Store string "ENTER NUMBER" in Bank 00
03 00 00           ;; Output the contents of Bank 00 to the LCD ("ENTER NUMBER")
04 01 01           ;; Store the button presses to Bank 01
03 00 00           ;; Output the contents of Bank 00 to the LCD ("ENTER NUMBER")
04 01 02           ;; Store the button presses to Bank 02
30 01 02           ;; Add Bank 02 to Bank 01
03 00 01           ;; Output the contents of Bank 01 (the sum of the addition)
```

The interpreter would replace the above with mnemonics as the user typed:

```
VAR @00 ENTER NUMBER  ;; Store string "ENTER NUMBER" in Bank 00
 << OUT @00           ;; Output the contents of Bank 00 to the LCD ("ENTER NUMBER")
 >>  IN @01           ;; Store the button presses to Bank 01
 << OUT @00           ;; Output the contents of Bank 00 to the LCD ("ENTER NUMBER")
 >>  IN @02           ;; Store the button presses to Bank 02
  + @01 @02           ;; Add Bank 02 to Bank 01
 << OUT @01           ;; Output the contents of Bank 01 (the sum of the addition)
```

# Add Two Numbers (with named banks)

Banks can also be given names, for readability:

```
00 ADD TWO NUMBERS  ;; Comment describing program
02 00 MSG           ;; Name Bank 00 "MSG"
02 01 A             ;; Name Bank 01 "A"
02 02 B             ;; Name Bank 02 "B"
10 00 ENTER NUMBER  ;; Store string "ENTER NUMBER" in MSG
03 00 00            ;; Output the contents of MSG to the LCD ("ENTER NUMBER")
04 01 01            ;; Store the button presses to A
03 00 00            ;; Output the contents of Bank 00 to the LCD ("ENTER NUMBER")
04 01 02            ;; Store the button presses to B
30 01 02            ;; Add B to A
03 00 01            ;; Output the contents of A (the sum of the addition)
```

The interpreter would replace the above with mnemonics as the user typed:

```
!!! ADD TWO NUMBERS    ;; Comment describing program
    @00 MSG            ;; Name Bank 00 "MSG"
    @01 A              ;; Name Bank 01 "A"
    @02 B              ;; Name Bank 02 "B"
VAR MSG ENTER NUMBER   ;; Store string "ENTER NUMBER" in MSG
 << OUT MSG            ;; Output the contents of Bank 00 to the LCD ("ENTER NUMBER")
 >>  IN A              ;; Store the button presses to Bank 01
 << OUT MSG            ;; Output the contents of Bank 00 to the LCD ("ENTER NUMBER")
 >>  IN B              ;; Store the button presses to Bank 02
  + A B                ;; Add Bank 02 to Bank 01
 << OUT A              ;; Output the contents of Bank 01 (the sum of the addition)
```
