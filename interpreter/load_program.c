#include "load_program.h"
#include "structures.h"

bool load_line_into_program(SnowflakeProgram *program, char *line)
{
    // Programs are of the format:
    //
    // INSTRUCTION [PARAMETER] [PARAMETER] [;; COMMENT]
    //
    // Line parsing rules:
    //
    // * The first non-whitespace text is the instruction
    // * The instruction ends at the first whitespace
    // * If there are two parameters: 
    //     - the first whitespace separates the first parameter from the second
    //     - the second whitespace to the end belongs to the second parameter
    // * If there is one parameter:
    //     - the whitespace belongs to the first parameter
    // * Exception:
    //     - everything after the whitespace that precedes ";;" is ignored
    //

    return true;
}