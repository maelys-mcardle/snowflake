#include <stdlib.h>
#include <math.h>
#include "platforms/logging.h"
#include "core/devices.h"
#include "core/array.h"
#include "core/string.h"
#include "print_program.h"

/* Prints an entire Snowflake program. */
char *get_printable_program(Program *program, LineNumbering line_numbering)
{
    log_debug("Printing program...\n");
    char *program_string = NULL;

    if (program != NULL && 
        program->instructions != NULL)
    {
        InstructionCount total_instructions = get_instruction_count(program);
        char *line_number_format = get_printable_line_number_format(total_instructions);

        for (InstructionPointer i = 0; i < total_instructions; i++)
        {
            log_debug("[Instruction %02i]\n", i);
            Instruction *instruction = get_instruction(program, i);
            char *instruction_string = get_printable_instruction(program, instruction);

            if (line_numbering == WITH_LINE_NUMBER)
            {
                char *line_number_string = get_printable_line_number(line_number_format, i);
                if (line_number_string != NULL)
                {
                    program_string = append_string(program_string, line_number_string);
                    free(line_number_string);
                }
            }

            if (instruction_string != NULL)
            {
                program_string = append_string(program_string, instruction_string);
                free(instruction_string);
            }
        }

        if (line_number_format != NULL)
        {
            free(line_number_format);
        }
    }

    return program_string; 
}

char *get_printable_line_number_format(InstructionCount total_lines)
{
    unsigned int digits_wide = 1;
    char string_format[MAX_IDENTIFIER_SIZE + 2];

    while (total_lines + 1 > pow(10, digits_wide))
    {
        digits_wide++; 
    }
    
    snprintf(string_format, sizeof(string_format), "%%0%ii ", digits_wide);
    return append_string(NULL, string_format);
}

char *get_printable_line_number(char *string_format, InstructionCount current_line)
{
    if (string_format == NULL)
    {
        return NULL;
    }

    char line_number[MAX_IDENTIFIER_SIZE + 2];
    snprintf(line_number, sizeof(line_number), string_format, current_line + 1);
    return append_string(NULL, line_number);
}

/* Prints a line of Snowflake. */
char *get_printable_instruction(Program *program, Instruction *instruction)
{
    bool instruction_exists = false;
    InstructionInfo instruction_info = get_instruction_info(
        instruction->instruction, &instruction_exists);

    // If instruction doesn't exist, return NULL.
    if (!instruction_exists)
    {
        return NULL;
    }

    // Get mnemonic.
    char *instruction_string = append_string(NULL, instruction_info.mnemonic);

    // Get first parameter.
    char *first_parameter = get_printable_parameter(
        program,
        instruction->instruction,
        instruction_info.parameters.first, 
        instruction->parameters.first);

    if (first_parameter != NULL)
    {
        instruction_string = append_string(instruction_string, " ");
        instruction_string = append_string(instruction_string, first_parameter);
        free(first_parameter);
    }

    // Get second parameter.
    char *second_parameter = get_printable_parameter(
        program,
        instruction->instruction,
        instruction_info.parameters.second, 
        instruction->parameters.second);
    
    if (second_parameter != NULL)
    {
        instruction_string = append_string(instruction_string, " ");
        instruction_string = append_string(instruction_string, second_parameter);
        free(second_parameter);
    }

    // Print end of line.
    return append_string(instruction_string, "\n");
}

/* Prints a parameter, if one is defined.
 * @return True if a parameter is defined; false if not.
 */
char *get_printable_parameter(Program *program, InstructionCode current_instruction, 
    ParameterType type, ParameterValue value)
{
    switch (get_parameter_type_without_flags(type))
    {
        case PARAMETER_NONE:
            return NULL;
        case PARAMETER_BANK:
            return get_printable_identifier(program, current_instruction, 
                INSTRUCTION_NAME_BANK, value.identifier, "@%02i");
        case PARAMETER_LABEL:
            return get_printable_identifier(program, current_instruction, 
                INSTRUCTION_LABEL, value.identifier, ":%02i");
        case PARAMETER_TYPE:
            return get_printable_type(value.identifier);
        case PARAMETER_DEVICE:
            return get_printable_device(value.identifier);
        case PARAMETER_LITERAL:
            if (value.literal != NULL)
            {
                return append_string(NULL, value.literal);
            }
            return NULL;
        default:
            return NULL;
    }
}

char *get_printable_identifier(Program *program, InstructionCode current_instruction, 
    InstructionCode naming_instruction, int target_identifier, char *format)
{
    // Lookup name of label.
    if (current_instruction != naming_instruction)
    {
        char *identifier_name = get_name(program, naming_instruction, target_identifier);
        if (identifier_name != NULL)
        {
            return append_string(NULL, identifier_name);
        }
    }

    // Did not find name.
    char numeric_identifier[MAX_IDENTIFIER_SIZE];
    snprintf(numeric_identifier, MAX_IDENTIFIER_SIZE, format, target_identifier);
    return append_string(NULL, numeric_identifier);
}

/* Prints a device, if one is defined.
 * @return True if a device is defined; false if not.
 */
char *get_printable_device(int device)
{
    switch (device)
    {
        case DEVICE_OUT:
            return append_string(NULL, DEVICE_OUT_STRING);
        case DEVICE_IN:
            return append_string(NULL, DEVICE_IN_STRING);
        case DEVICE_BTN:
            return append_string(NULL, DEVICE_BTN_STRING);
        case DEVICE_RND:
            return append_string(NULL, DEVICE_RND_STRING);
        default:
            return NULL;
    }
}

char *get_printable_type(int type)
{
    switch (type)
    {
        case TYPE_VARIABLE:
            return append_string(NULL, TYPE_VARIABLE_STRING);
        case TYPE_BOOLEAN:
            return append_string(NULL, TYPE_BOOLEAN_STRING);
        case TYPE_INTEGER:
            return append_string(NULL, TYPE_INTEGER_STRING);
        case TYPE_FLOAT:
            return append_string(NULL, TYPE_FLOAT_STRING);
        case TYPE_STRING:
            return append_string(NULL, TYPE_STRING_STRING);
        case TYPE_ARRAY:
            return append_string(NULL, TYPE_ARRAY_STRING);
        default:
            return NULL;
    }
}

char *get_name(Program *program, InstructionCode naming_instruction, int target_identifier)
{
    for (InstructionPointer i = 0; i < get_instruction_count(program); i++)
    {
        Instruction *instruction = get_instruction(program, i);
        if (instruction->instruction == naming_instruction &&
            instruction->parameters.first.identifier == target_identifier)
        {
            return instruction->parameters.second.literal;
        }
    }

    return NULL;
}
