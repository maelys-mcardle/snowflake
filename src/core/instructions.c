#include <stdlib.h>
#include "headers/instructions.h"
#include "headers/logging.h"
#include "headers/bank.h"

Instruction *new_instruction()
{
    Instruction *instruction = (Instruction *) malloc(sizeof(Instruction));
    return instruction;
}

void free_instruction(void *instruction_ptr)
{
    Instruction *instruction = (Instruction *) instruction_ptr;
    if (instruction != NULL)
    {
        bool instruction_exists = false;
        InstructionInfo info = get_instruction_info(
            instruction->instruction, &instruction_exists);

        if (instruction_exists)
        {
            free_parameter(
                info.parameters.first, 
                instruction->parameters.first);

            free_parameter(
                info.parameters.second, 
                instruction->parameters.second);
        }

        free(instruction);
    }
}
