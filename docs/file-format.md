# Snowflake File Format

Snowflake programs are stored in plaintext ASCII as `.sn` files. 

The different fields are separated by spaces or tabs.

The different instructions are separated by a newline.

Mnemonics are not used in `.sn` files.

Any whitespace in a literal field is treated as part of that literal, except for the whitespace at the start or end. It is trimmed.

```
10 00 HELLO WORLD!    ;; Store "HELLO WORLD!" to Bank 00
03 00 00              ;; Output the contents of Bank 00 to the LCD
```

Anything that follows the last `;;` is treated as a comment and ignored. These comments
may not be displayed in an interpreter. Empty lines are ignored.
