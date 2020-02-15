#include <stdio.h>
#include "load_program.h"
#include "structures.h"

/* Loads a line of text into the program. */
bool load_line_into_program(SnowflakeProgram *program, char *line, int max_line_length)
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
    //     - everything after the whitespace that precedes the first ";;" is ignored
    //

    // Remove comments from the line.
    discard_comment(line, max_line_length);

    printf("%s", line);

    return true;
}

/* Discards the comment on the line. 
 * @return true if comment was removed, false otherwise.
*/
bool discard_comment(char *line, int max_line_length)
{
    bool last_char_is_semicolon = false;
    // Remove anything that follows the ";;"
    for (int index = 0; index < max_line_length; index++) {

        // Second ";" found.
        if (line[index] == COMMENT_SYMBOL &&
            last_char_is_semicolon) {

            // End the line here.
            line[index-1] = '\0';
            return true;
        }

        // First ";" found.
        else if (line[index] == COMMENT_SYMBOL) {
            last_char_is_semicolon = true;
        }

        // Any other character found.
        else {
            last_char_is_semicolon = false;
        }
    }

    return false;
}