#include <stdlib.h>
#include "core/headers/output.h"
#include "core/headers/devices.h"
#include "headers/print_program.h"

/* Prints an entire Snowflake program. */
void print_program(Program *program)
{
    log_debug("Printing program...\n");

    if (program != NULL && 
        program->instructions.instructions != NULL && 
        program->instructions.count > 0)
    {
        for (int i = 0; i < program->instructions.count; i++)
        {
            log_debug("[Instruction %02i]\n", i);
            Instruction *instruction = program->instructions.instructions[i];
            print_instruction(program, instruction);
        }
    }
}

/* Prints a line of Snowflake. */
void print_instruction(Program *program, Instruction *instruction)
{
    // Print mnemonic.
    printf("%c%c%c ",
        instruction->info.mnemonic[0],
        instruction->info.mnemonic[1],
        instruction->info.mnemonic[2]);

    // Print first parameter.
    bool has_parameter = print_parameter(
        program,
        instruction->instruction,
        instruction->info.parameters.first, 
        instruction->parameters.first);

    // Print the space that separates the parameter.
    if (has_parameter)
    {
        printf(" ");
    }

    // Print second parameter.
    print_parameter(
        program,
        instruction->instruction,
        instruction->info.parameters.second, 
        instruction->parameters.second);

    // Print end of line.
    printf("\n");
}

/* Prints a parameter, if one is defined.
 * @return True if a parameter is defined; false if not.
 */
bool print_parameter(Program *program, short current_instruction, ParameterType type, ParameterValue value)
{
    switch (get_parameter_type(type))
    {
        case PARAMETER_NONE:
            return false;
        case PARAMETER_BANK:
            print_identifier(program, current_instruction, INSTRUCTION_NAME_BANK, value.integer, "@%02i");
            return true;
        case PARAMETER_LABEL:
            print_identifier(program, current_instruction, INSTRUCTION_LABEL, value.integer, ":%02i");
            return true;
        case PARAMETER_DEVICE:
            return print_device(value.integer);
        case PARAMETER_LITERAL:
            if (value.string != NULL)
            {
                printf("%s", value.string);
                return true;
            }
            return false;
        default:
            return false;
    }
}

void print_identifier(Program *program, short current_instruction, short naming_instruction, int target_identifier, char *format)
{
    bool found_name = false;

    // Lookup name of label.
    if (current_instruction != naming_instruction)
    {
        char *identifier_name = get_name(program, naming_instruction, target_identifier);
        if (identifier_name != NULL)
        {
            printf("%s", identifier_name);
            found_name = true;
        }
    }

    if (!found_name)
    {
        printf(format, target_identifier);
    }
}

char *get_name(Program *program, short naming_instruction, int target_identifier)
{
    for (int i = 0; i < program->instructions.count; i++)
    {
        Instruction *instruction = program->instructions.instructions[i];
        if (instruction->instruction == naming_instruction &&
            instruction->parameters.first.integer == target_identifier)
        {
            return instruction->parameters.second.string;
        }
    }

    return NULL;
}

/* Prints a device, if one is defined.
 * @return True if a device is defined; false if not.
 */
bool print_device(int device)
{
    switch (device)
    {
        case DEVICE_OUT:
            printf(DEVICE_OUT_STRING);
            return true;
        case DEVICE_IN:
            printf(DEVICE_IN_STRING);
            return true;
        case DEVICE_PRT:
            printf(DEVICE_PRT_STRING);
            return true;
        case DEVICE_BTN:
            printf(DEVICE_BTN_STRING);
            return true;
        default:
            return false;
    }
}
