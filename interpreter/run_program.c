#include <stdlib.h>
#include "headers/run_program.h"
#include "headers/output.h"

void run_program(Program *program)
{
    log_debug("Executing program...\n");

    if (program != NULL && 
        program->instructions.instructions != NULL && 
        program->instructions.count > 0)
    {
        int instruction_pointer = 0;
        while (instruction_pointer < program->instructions.count)
        {
            Instruction *instruction = program->instructions.instructions[instruction_pointer];
            run_instruction(program, instruction, &instruction_pointer);
        }
    }
}

void run_instruction(Program *program, Instruction *instruction, int *instruction_pointer)
{
    *instruction_pointer += 1;
    return;
}