#include <stdlib.h>
#include <math.h>
#include "platforms/logging.h"
#include "core/devices.h"
#include "core/array.h"
#include "core/string.h"
#include "print/print_instruction.h"

/** 
 * Prints a line of Snowflake.
 *
 * @param program the entire program.
 * @param instruction the instruction to display. 
 */
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
    char *instruction_string = new_string(instruction_info.mnemonic);

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
    return instruction_string;
}

/**
 * Prints a parameter, if one is defined.
 * 
 * @param program the snowflake program.
 * @param current_instruction the code for the current instruction.
 * @param type the parameter type.
 * @param value the parameter value.
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
                return new_string(value.literal);
            }
            return NULL;
        default:
            return NULL;
    }
}

/**
 * Get the stringified identifier.
 * 
 * These identifiers can be labels, banks, etc. If an instruction was used to name
 * these identifiers, it tries to locate it so that what's displayed is this name.
 * If the identifier (eg. label, bank) was never given a name, then it's numeric
 * value is displayed.
 * 
 * @param program the snowflake program.
 * @param current_instruction the code for the current instruction.
 * @param naming_instruction the code for the instruction that names this identifier.
 * @param target_identifier the identifier defined by the naming instruction.
 * @param format the format to display the identifier.
 * @return the stringified identifier.
 */
char *get_printable_identifier(Program *program, InstructionCode current_instruction, 
    InstructionCode naming_instruction, int target_identifier, char *format)
{
    // Lookup name of label.
    if (current_instruction != naming_instruction)
    {
        char *identifier_name = get_name(program, naming_instruction, target_identifier);
        if (identifier_name != NULL)
        {
            return new_string(identifier_name);
        }
    }

    // Did not find name.
    char numeric_identifier[MAX_IDENTIFIER_SIZE];
    snprintf(numeric_identifier, MAX_IDENTIFIER_SIZE, format, target_identifier);
    return new_string(numeric_identifier);
}

/** 
 * Gets the stringified device, if one is defined.
 * 
 * @param device the device type.
 * @return The stringified device.
 */
char *get_printable_device(int device)
{
    switch (device)
    {
        case DEVICE_OUT:
            return new_string(DEVICE_OUT_STRING);
        case DEVICE_IN:
            return new_string(DEVICE_IN_STRING);
        case DEVICE_BTN:
            return new_string(DEVICE_BTN_STRING);
        case DEVICE_RND:
            return new_string(DEVICE_RND_STRING);
        default:
            return NULL;
    }
}

/** 
 * Gets the stringified type, if one is defined.
 * 
 * @param type the type type.
 * @return The stringified type.
 */
char *get_printable_type(int type)
{
    switch (type)
    {
        case TYPE_VARIABLE:
            return new_string(TYPE_VARIABLE_STRING);
        case TYPE_BOOLEAN:
            return new_string(TYPE_BOOLEAN_STRING);
        case TYPE_INTEGER:
            return new_string(TYPE_INTEGER_STRING);
        case TYPE_FLOAT:
            return new_string(TYPE_FLOAT_STRING);
        case TYPE_STRING:
            return new_string(TYPE_STRING_STRING);
        case TYPE_ARRAY:
            return new_string(TYPE_ARRAY_STRING);
        default:
            return NULL;
    }
}

/**
 * Locates the name for the target identifier in the program.
 * 
 * @param program the program.
 * @param naming_instruction the instruction that assigns a name to the identifier.
 * @param target_identifier the identifier to look for that might have been given a name.
 * @return the name for the parameter. NULL if no name was found.
 */
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
