#include <stdlib.h>
#include <string.h>
#include "parse_instruction.h"
#include "errors.h"
#include "platforms/logging.h"
#include "core/instructions.h"
#include "core/string.h"
#include "core/type_conversion.h"
#include "core/parameters.h"

/* Parses the line, and if its a valid instruction, appends it to the program. */
bool parse_instruction(Program *program, char *line, int max_line_length)
{
    Instruction *instruction = new_instruction();
    if (instruction != NULL)
    {
        bool instruction_valid = parse_instruction_from_line(instruction, line, max_line_length);
        if (instruction_valid)
        {
            bool appended_instruction = append_instruction_to_program(program, instruction);
            if (!appended_instruction)
            {
                log_error(ERROR_MESG_COULD_NOT_APPEND_INSTRUCTION);
                free_instruction(instruction);
            }
            return appended_instruction;
        }
        else
        {
            log_debug("Invalid instruction: line ignored.\n");
            free_instruction(instruction);
        }
    }
    else
    {
        log_error(ERROR_MESG_COULD_NOT_ALLOCATE_MEMORY);
    }

    return false;
}

/* Loads a line of text into the program.
 * @return true if a line contained an instruction, false if not.
 */
bool parse_instruction_from_line(Instruction *instruction, char *line, int max_line_length)
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
    //     - instructions determine how many parameters are taken.
    // * Parameters:
    //     - LABEL/BANK/DEVICE are read up to the first whitespace
    //     - Only the first three characters are looked at
    //     - LITERALs consume all the whitespace
    //     - Whitespace at the end of a LITERAL is ignored
    // * Comments:
    //     - everything after ";;" is ignored
    //

    // Remove comments from the line.
    strip_comment(line, max_line_length);

    // Load the instruction.
    //  * The instruction is extracted from the line of text.
    //  * Information about that instruction is retrieved.
    bool instruction_extracted = false;
    bool instruction_exists = false;
    int line_cursor = extract_instruction(line, max_line_length, &(instruction->instruction),
        &instruction_extracted);

    if (instruction_extracted)
    {
        InstructionInfo instruction_info = get_instruction_info(
            instruction->instruction, &instruction_exists);

        // Instruction exists.
        if (instruction_exists)
        {
            // Note instruction exists.
            log_debug("Found instruction %02i ('%s')\n", 
                instruction->instruction,
                instruction_info.mnemonic);

            // Keep track of whether parameters were parsed ok.
            bool first_parameter_missing = true;
            bool second_parameter_missing = true;

            // Load first parameter.
            line_cursor = extract_parameter(line, max_line_length, line_cursor,
                instruction_info.parameters.first, &(instruction->parameters.first),
                &first_parameter_missing);

            if (first_parameter_missing)
            {
                log_error(ERROR_MESG_PARAMETER_MISSING, instruction->instruction, 1);
            }

            // Load second parameter.
            line_cursor = extract_parameter(line, max_line_length, line_cursor,
                instruction_info.parameters.second, &(instruction->parameters.second),
                &second_parameter_missing);

            if (second_parameter_missing)
            {
                log_error(ERROR_MESG_PARAMETER_MISSING, instruction->instruction, 2);
            }

            // Return if parameters were ok.
            bool parameter_missing = first_parameter_missing || second_parameter_missing;
            return !parameter_missing;
        }
    }

    // No instruction parsed.
    return false;
}

int extract_parameter(char *line, int max_line_length, int start_position,
            ParameterType parameter_type, ParameterValue *parameter_value,
            bool *parameter_missing)
{
    // No parameter to process.
    if (is_parameter_none(parameter_type))
    {
        *parameter_missing = false;
        return start_position;
    }

    // Stop at whitespace for all parameter types except literals.
    bool is_literal = is_parameter_literal(parameter_type);
    bool stop_at_whitespace = !is_literal;
    size_t max_parameter_size = MAX_PARAMETER_SIZE;
    char parameter_string[max_parameter_size];

    // Parse the field. Start at the starting point.
    int end_position = parse_field(line, max_line_length, stop_at_whitespace, 
        start_position, parameter_string, max_parameter_size);

    // Trim whitespace.
    strip_end_whitespace(parameter_string, max_parameter_size);
    
    // Has a parameter.
    bool has_parameter_string = !is_string_end(parameter_string[0]);
    bool stored_parameter = false;
    if (has_parameter_string)
    {
        stored_parameter = store_parameter(
            parameter_type, parameter_string, 
            max_parameter_size, parameter_value);
    }
    else
    {
        parameter_value->literal = NULL;
    }

    // Determine if the parameter is missing.
    bool parameter_required = !is_parameter_optional(parameter_type);
    *parameter_missing = (stored_parameter == false && parameter_required);

    return end_position;
}

bool store_parameter(ParameterType parameter_type, char *parameter_string, int max_parameter_size, ParameterValue *parameter_value)
{
    // Store the parameter.
    // * Literals are stored as strings.
    // * Banks, devices, labels as integers.
    if (is_parameter_literal(parameter_type))
    {
        // If it's a literal, allocate memory, and copy the string.
        size_t allocation_size = strnlen(parameter_string, max_parameter_size);
        parameter_value->literal = malloc(allocation_size + 1);
        
        if (parameter_value->literal != NULL)
        {
            strncpy(parameter_value->literal, parameter_string, allocation_size);
            parameter_value->literal[allocation_size] = CHAR_END_STRING;
            return true;
        }
        else
        {
            log_error(ERROR_MESG_COULD_NOT_ALLOCATE_MEMORY);
        }
    }
    else
    {
        // If it's any other value (banks, devices, labels, type) interpret as integer.
        bool parsed_integer_ok;
        parameter_value->identifier = string_to_integer(parameter_string, &parsed_integer_ok);
        
        if (parsed_integer_ok)
        {
            return true;
        }
        else
        {
            log_error(ERROR_MESG_COULD_NOT_PARSE_INTEGER, parameter_string);
        } 
    }
    return false;
}

/* Extracts the instruction from the line.
 * @return the last character with the position.
 */
int extract_instruction(char *line, int max_line_length, InstructionCode *instruction, bool *instruction_extracted)
{
    char max_instruction_size = MAX_INSTRUCTION_SIZE;
    char instruction_string[max_instruction_size];
    *instruction_extracted = false;
    *instruction = 0;

    // Load instruction text.
    int end = parse_field(line, max_line_length, true, 
        0, instruction_string, max_instruction_size);

    // If text associated with an instruction was loaded, parse it.
    if (!is_string_end(instruction_string[0])) 
    {
        // Parse the instruction from text to an integer.
        bool parse_to_integer_ok = false;
        *instruction = string_to_integer(instruction_string, &parse_to_integer_ok);
        *instruction_extracted = parse_to_integer_ok;
    }

    return end;
}

/* Extracts the instruction from the line.
 * @return the last character with the position.
 */
int parse_field(char *line, int max_line_length, bool stop_at_whitespace, 
    int start, char *output, int max_output_size)
{
    int index = 0;
    int output_index = 0;

    // Terminate the tring, in case nothing is loaded.
    output[0] = CHAR_END_STRING;

    // Remove anything that follows the ";;"
    for (index = 0; index < max_line_length; index++)
    {
        char character = line[index];

        // Stop at newline or break.
        if (is_string_end(character) ||
            index == max_line_length - 1 ||
            output_index == max_output_size - 1)
        {
            output[output_index] = CHAR_END_STRING;
            return index;
        }

        // If this is before the line start, ignore it.
        // This is only to capture newlines.
        else if (index < start)
        {
            continue;
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
        else
        {
            output[output_index] = character;
            output_index++;
        }
    }        

    return index;
}
