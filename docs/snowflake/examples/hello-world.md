# Hello World

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

