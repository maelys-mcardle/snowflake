#include <stdlib.h>
#include <stdio.h>
#include "headers/program.h"
#include "headers/errors.h"

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

void print_snowflake_program(Program *program)
{
    if (program != NULL && 
        program->instructions.instructions != NULL && 
        program->instructions.count > 0)
    {
        for (int i = 0; i < program->instructions.count; i++)
        {
            Instruction *instruction = program->instructions.instructions[i];

            // Print mnemonic.
            print("%c%c%c ",
                instruction->info.mnemonic[0],
                instruction->info.mnemonic[1],
                instruction->info.mnemonic[2]);

            // Print parameter.
            print_parameter(instruction->info.parameters.first, 
                instruction->parameters.first);
            print_parameter(instruction->info.parameters.second, 
                instruction->parameters.second);

            // Print end of line.
            print("\n");
        }
    }
}

void print_parameter(ParameterType type, ParameterValue value)
{
    ParameterType type_without_flags = type & PARAMETER_WITHOUT_FLAGS;
    switch (type_without_flags)
    {
        case PARAMETER_BANK:
            print("@%02i ", value.integer);
            break;
        case PARAMETER_LABEL:
            print(":%02i ", value.integer);
        case PARAMETER_DEVICE:
            print_device(value.integer);
            break;
        case PARAMETER_LITERAL:
            print("%s ", value.string);
            break;
        default:
            break;
    }
}

void print_device(int device)
{
    if (device == 0) print("OUT ");
    else if (device == 1) print("IN ");
    else if (device == 2) print("PRT ");
    else if (device == 3) print("BTN ");
    else print("??? ");
}
