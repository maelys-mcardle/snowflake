#include <stdio.h>
#include "load_program.h"
#include "structures.h"

/* Loads a line of text into the program. */
bool load_line_into_program(SnowflakeProgram *program, char *line)
{
    // Programs are of the format:
    //
    // INSTRUCTION [PARAMETER] [PARAMETER] [;; COMMENT] [\n]
    //
    // Line parsing rules:
    //
    // * Instructions:
    //     - the first non-whitespace text is the instruction
    //     - the instruction ends at the first whitespace
    //     - only the first three characters are looked at
    // * Instructions determine how many parameters are taken.
    // * If there are two parameters: 
    //     - the first whitespace separates the first parameter from the second
    //     - the second whitespace to the end belongs to the second parameter
    // * If there is one parameter:
    //     - the whitespace belongs to the first parameter
    // * Exception:
    //     - everything after the whitespace that precedes ";;" is ignored
    //

    discard_comment(line);

    printf("%s", line);

    return true;
}

void discard_comment(char *line)
{
    // Remove anything that follows the ";;"
    
}