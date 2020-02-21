#include <stdlib.h>
#include <stdio.h>
#include "headers/program.h"
#include "headers/errors.h"
#include "headers/output.h"

/* Creates a new program and allocates memory.
 * @return The initialized program.
 */
Program *new_program()
{
    Program *program = (Program *) malloc(sizeof(Program));
    if (program != NULL)
    {
        program->instructions.count = 0;
        program->instructions.instructions = NULL;
    }
    return program;
}

/* Free the allocated data for the program. */
void free_program(Program *program)
{
    if (program != NULL)
    {
        // Free all the instructions.
        if (program->instructions.instructions != NULL && 
            program->instructions.count > 0)
        {
            for (int i = 0; i < program->instructions.count; i++)
            {
                free_instruction(program->instructions.instructions[i]);
            }
        }

        // Free the program.
        free(program);
    }
}

/* Adds an instruction to the program.
 * @return True if the instruction was added, false if not.
 */
bool append_instruction_to_program(Program *program, Instruction *instruction)
{
    int new_count = program->instructions.count + 1;
    int new_instruction_array_size = sizeof(Instruction *) * new_count;
    Instruction** new_array = (Instruction**) realloc(
        program->instructions.instructions, 
        new_instruction_array_size);

    if (new_array != NULL)
    {
        int last_item = new_count - 1;
        program->instructions.instructions = new_array;
        program->instructions.count = new_count;
        program->instructions.instructions[last_item] = instruction;
        return true;
    }
    else
    {
        log_error(ERROR_MESG_COULD_NOT_ALLOCATE_MEMORY);
        return false;
    }
}

/* Prints an entire Snowflake program. */
void print_snowflake_program(Program *program)
{
    if (program != NULL && 
        program->instructions.instructions != NULL && 
        program->instructions.count > 0)
    {
        for (int i = 0; i < program->instructions.count; i++)
        {
            Instruction *instruction = program->instructions.instructions[i];
            void print_snowflake_instruction(instruction)
        }
    }
}

/* Prints a line of Snowflake. */
void print_snowflake_instruction(Instruction *instruction)
{
    // Print mnemonic.
    print("%c%c%c ",
        instruction->info.mnemonic[0],
        instruction->info.mnemonic[1],
        instruction->info.mnemonic[2]);

    // Print first parameter.
    bool has_parameter = print_parameter(
        instruction->info.parameters.first, 
        instruction->parameters.first);

    // Print the space that separates the parameter.
    if (has_parameter) {
        print(" ");
    }

    // Print second parameter.
    print_parameter(
        instruction->info.parameters.second, 
        instruction->parameters.second);

    // Print end of line.
    print("\n");
}

/* Prints a parameter, if one is defined.
 * @return True if a parameter is defined; false if not.
 */
bool print_parameter(ParameterType type, ParameterValue value)
{
    ParameterType type_without_flags = type & PARAMETER_WITHOUT_FLAGS;
    switch (type_without_flags)
    {
        case PARAMETER_NONE:
            return false;
        case PARAMETER_BANK:
            print("@%02i", value.integer);
            return true;
        case PARAMETER_LABEL:
            print(":%02i", value.integer);
            return true;
        case PARAMETER_DEVICE:
            return print_device(value.integer);
        case PARAMETER_LITERAL:
            print("%s", value.string);
            return true;
        default:
            return false;
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
