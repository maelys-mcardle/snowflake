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
void print_program(Program *program)
{
    if (program != NULL && 
        program->instructions.instructions != NULL && 
        program->instructions.count > 0)
    {
        for (int i = 0; i < program->instructions.count; i++)
        {
            Instruction *instruction = program->instructions.instructions[i];
            print_instruction(instruction);
        }
    }
}

