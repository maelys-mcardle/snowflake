#include <stdlib.h>
#include "headers/output.h"
#include "headers/print_program.h"

/* Prints an entire Snowflake program. */
void print_program(Program *program)
{
    if (program != NULL && 
        program->instructions.instructions != NULL && 
        program->instructions.count > 0)
    {
        for (int i = 0; i < program->instructions.count; i++)
        {
            Instruction *instruction = program->instructions.instructions[i];
            print_instruction(program, instruction);
        }
    }
}

/* Prints a line of Snowflake. */
void print_instruction(Program *program, Instruction *instruction)
{
    // Print mnemonic.
    print("%c%c%c ",
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
        print(" ");
    }

    // Print second parameter.
    print_parameter(
        program,
        instruction->instruction,
        instruction->info.parameters.second, 
        instruction->parameters.second);

    // Print end of line.
    print("\n");
}

/* Prints a parameter, if one is defined.
 * @return True if a parameter is defined; false if not.
 */
bool print_parameter(Program *program, int current_instruction, ParameterType type, ParameterValue value)
{
    ParameterType type_without_flags = type & PARAMETER_WITHOUT_FLAGS;
    switch (type_without_flags)
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
                print("%s", value.string);
                return true;
            }
            return false;
        default:
            return false;
    }
}

void print_identifier(Program *program, int current_instruction, int naming_instruction, int target_identifier, char *format)
{
    bool found_name = false;

    // Lookup name of label.
    if (current_instruction != naming_instruction)
    {
        char *identifier_name = get_name(program, naming_instruction, target_identifier);
        if (identifier_name != NULL)
        {
            print("%s", identifier_name);
            found_name = true;
        }
    }

    if (!found_name)
    {
        print(format, target_identifier);
    }
}

char *get_name(Program *program, int naming_instruction, int target_identifier)
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
}

/* Prints a device, if one is defined.
 * @return True if a device is defined; false if not.
 */
bool print_device(int device)
{
    switch (device)
    {
        case 0:
            print("OUT");
            return true;
        case 1:
            print(" IN");
            return true;
        case 2:
            print("PRT");
            return true;
        case 3:
            print("BTN");
            return true;
        default:
            return false;
    }
}
