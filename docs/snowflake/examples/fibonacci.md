# Fibonacci Sequence

The following calculates the Fibonacci Sequence up to a user-defined number.

```
03 01 00  ;; User enters MAX. Stored in Bank 00.
12 01 01  ;; CURRENT NUMBER (Bank 01) is set to 1.
12 02 01  ;; LAST NUMBER (Bank 02) is set to 1.
00 00     ;; Start of loop
04 03 01  ;; SUM = CURRENT NUMBER
30 03 02  ;; SUM = SUM + LAST NUMBER
02 00 03  ;; Output value of SUM
24 03 00  ;; If SUM > MAX
20 01     ;; ...go to end.
04 02 01  ;; CURRENT NUMBER becomes LAST NUMBER
04 03 02  ;; SUM becomes CURRENT NUMBER
20 00     ;; Start loop over.
00 01     ;; End
```

The interpreter would replace the above with mnemonics as the user typed:

```
 >>  IN @00  ;; User enters MAX. Stored in Bank 00.
INT @01 01   ;; CURRENT NUMBER (Bank 01) is set to 1.
INT @02 01   ;; LAST NUMBER (Bank 02) is set to 1.
### :00      ;; Start of loop
  = @03 @01  ;; SUM = CURRENT NUMBER
  + @03 @02  ;; SUM = SUM + LAST NUMBER
 << OUT @03  ;; Output value of SUM
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
24 03 00      ;; If SUM > MAX
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
 >>  IN MAX             ;; User enters MAX. Stored in Bank 00.
INT CURRENT 01          ;; CURRENT NUMBER (Bank 01) is set to 1.
INT LAST 01             ;; LAST NUMBER (Bank 02) is set to 1.
### START               ;; Start of loop
  = SUM CURRENT         ;; SUM = CURRENT NUMBER
  + SUM LAST            ;; SUM = SUM + LAST NUMBER
 << OUT SUM             ;; Output value of SUM
IF> SUM MAX             ;; If SUM > MAX
 -> END                 ;; ...go to end.
  = LAST CURRENT        ;; ...otherwise CURRENT NUMBER becomes LAST NUMBER
  = CURRENT SUM         ;; SUM becomes CURRENT NUMBER
 -> START               ;; Start loop over.
### END                 ;; End
```
