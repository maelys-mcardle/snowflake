#include <stdio.h>
#include "load_program.h"
#include "structures.h"

/* Loads a line of text into the program.
 * @return true if a line contained an instruction, false if not.
 */
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

    // Load the instruction.
    char instruction;
    int cursor = parse_instruction(line, max_line_length, &instruction);

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

        char character = line[index];

        // Stop at newline or break.
        if (is_string_end(character))
        {
            return false;
        }

        // Second ";" found.
        else if (character == CHAR_COMMENT &&
            last_char_is_semicolon)
        {

            // Set end the line here.
            line[index-1] = CHAR_END_STRING;
            return true;
        }

        // First ";" found.
        else if (character == CHAR_COMMENT)
        {
            last_char_is_semicolon = true;
        }

        // Any other character found.
        else
        {
            last_char_is_semicolon = false;
        }
    }

    return false;
}

/* Extracts the instruction from the line.
 * @return the last character with the position.
 */
int parse_instruction(char *line, int max_line_length, char *instruction)
{
    int index = 0;
    char max_instruction_size = 3;
    char instruction_string[max_instruction_size];
    char instruction_index = 0;

    int end = parse_field(line, max_line_length, true, 
        0, instruction_string, max_instruction_size);

    return end;
}

/* Extracts the instruction from the line.
 * @return the last character with the position.
 */
int parse_field(char *line, int max_line_length, bool stop_at_whitespace, 
    int start, char *output, int max_output_size)
{
    int index = start;
    char output_index = 0;

    // Remove anything that follows the ";;"
    for (index; index < max_line_length; index++) {
        char character = line[index];

        // Stop at newline or break.
        if (is_string_end(character) ||
            output_index == max_output_size - 1)
        {
            output[output_index] = CHAR_END_STRING;
            return index;
        }

        // Ignore whitespace before instruction.
        if (output_index == 0 &&
            is_whitespace(character))
        {
            // do nothing.
        }

        // Whitespace after instruction is understood
        // as the end of the instruction.
        else if (stop_at_whitespace && 
            output_index > 0 &&
            is_whitespace(character))
        {
            // End it here.
            output[output_index] = CHAR_END_STRING;
            return index;
        }

        // Load text in between.
        else {
            output[output_index] = character;
            output_index++;
        }
    }        

    return index;
}

bool is_whitespace(char character)
{
    switch (character) {
        case CHAR_SPACE:
        case CHAR_TAB:
            return true;
        default:
            return false;
    }
}

bool is_string_end(char character)
{
       switch (character) {
        case CHAR_NEWLINE:
        case CHAR_END_STRING:
            return true;
        default:
            return false;
    } 
}