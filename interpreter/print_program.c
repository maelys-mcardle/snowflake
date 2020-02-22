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
        instruction->info.parameters.second, 
        instruction->parameters.second);

    // Print end of line.
    print("\n");
}

/* Prints a parameter, if one is defined.
 * @return True if a parameter is defined; false if not.
 */
bool print_parameter(Program *program, ParameterType type, ParameterValue value)
{
    ParameterType type_without_flags = type & PARAMETER_WITHOUT_FLAGS;
    switch (type_without_flags)
    {
        case PARAMETER_NONE:
            return false;
        case PARAMETER_BANK:
            print_bank(program, value.integer);
            return true;
        case PARAMETER_LABEL:
            print_label(program, value.integer);
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

void print_label(Program *program, int label)
{
    // Lookup name of label.
    char *label_name = get_name(program, INSTRUCTION_LABEL, label);
    if (label_name != NULL)
    {
        print("%s", label_name);
    }
    else
    {
        print(":%02i", label);
    }
}

void print_bank(Program *program, int bank)
{
    // Lookup name of bank.
    char *bank_name = get_name(program, INSTRUCTION_NAME_BANK, bank);
    if (bank_name != NULL)
    {
        print("%s", bank_name);
    }
    else
    {
        print("@%02i", bank);
    }
}

char *get_name(Program *program, int target_instruction, int target_identifier)
{
    for (int i = 0; i < program->instructions.count; i++)
    {
        Instruction *instruction = program->instructions.instructions[i];
        if (instruction->instruction == target_instruction &&
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
