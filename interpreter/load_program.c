#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "headers/load_program.h"
#include "headers/structures.h"
#include "headers/instructions.h"

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
    //  * The instruction is extracted from the line of text.
    //  * Information about that instruction is retrieved.
    int instruction;
    bool instruction_exists;
    int cursor = extract_instruction(line, max_line_length, &instruction);
    InstructionInfo instruction_info = get_instruction_info(instruction, &instruction_exists);

    // Instruction exists.
    if (instruction_exists) {
        printf("%s", instruction_info.mnemonic);

        // Load first parameter.

        // Load second parameter.

        return true;
    }

    // No instruction parsed.
    return false;
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
int extract_instruction(char *line, int max_line_length, int *instruction)
{
    int index = 0;
    char max_instruction_size = 3;
    char instruction_string[max_instruction_size];
    char instruction_index = 0;

    // Load instruction text.
    int end = parse_field(line, max_line_length, true, 
        0, instruction_string, max_instruction_size);

    // If text associated with an instruction was loaded, parse it.
    if (!is_string_end(instruction_string[0])) 
    {
        // Parse the instruction from text to an integer.
        bool instruction_ok = false;
        *instruction = parse_integer(&instruction_ok, instruction_string);

        // Could not parse instruction into an integer.
        if (!instruction_ok) {
            *instruction = -1;
        }

    // No text was loaded.
    } else {
        *instruction = -1;
    }

    return end;
}

int parse_integer(bool *ok, char *string)
{
    int integer;
    char *end_pointer;

    // Reset errno. If strtol fails this will change.
    errno = 0;

    // Parse the string into an integer.
    integer = strtol(string,  &end_pointer, 10);

    // Indicate error.
    if (end_pointer == string || errno != 0) {
        *ok = false;
    } else {
        *ok = true;
    }

    return integer;
}

/* Extracts the instruction from the line.
 * @return the last character with the position.
 */
int parse_field(char *line, int max_line_length, bool stop_at_whitespace, 
    int start, char *output, int max_output_size)
{
    int index = start;
    char output_index = 0;

    // Terminate the tring, in case nothing is loaded.
    output[0] = CHAR_END_STRING;

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
        else if (output_index == 0 &&
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

bool strip_end_whitespace(char *string, int max_string_length)
{
    int whitespace_start = 0;
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