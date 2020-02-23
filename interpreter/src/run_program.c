#include <stdlib.h>
#include "headers/run_program.h"
#include "headers/output.h"
#include "headers/type_conversion.h"
#include "headers/bank.h"

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

bool run_instruction(Program *program, Instruction *instruction, int *instruction_pointer)
{
    log_debug("[Executing %02i] %c%c%c\n",
        *instruction_pointer,
        instruction->info.mnemonic[0],
        instruction->info.mnemonic[1],
        instruction->info.mnemonic[2]);

    bool instruction_ok = true;

    switch (instruction->instruction)
    {
        case INSTRUCTION_COMMENT:
        case INSTRUCTION_LABEL:
        case INSTRUCTION_NAME_BANK:
            // no-op.
            *instruction_pointer += 1;
            break;
        case INSTRUCTION_OUTPUT:
        case INSTRUCTION_INPUT:
        case INSTRUCTION_COPY:
        case INSTRUCTION_TYPE:
        case INSTRUCTION_VARIABLE:
        case INSTRUCTION_BOOLEAN:
        case INSTRUCTION_INTEGER:
            instruction_ok = instruction_integer(program, instruction, instruction_pointer);
            break;
        case INSTRUCTION_FLOAT:
        case INSTRUCTION_STRING:
        case INSTRUCTION_ARRAY:
        case INSTRUCTION_JUMP_LABEL:
        case INSTRUCTION_JUMP_BANK:
        case INSTRUCTION_IF_EQUAL:
        case INSTRUCTION_IF_NOT_EQUAL:
        case INSTRUCTION_IF_GREATER_THAN:
        case INSTRUCTION_IF_LESSER_THAN:
        case INSTRUCTION_ADD:
        case INSTRUCTION_SUBTRACT:
        case INSTRUCTION_MULTIPLY:
        case INSTRUCTION_DIVIDE:
        case INSTRUCTION_POWER:
        case INSTRUCTION_NOT:
        case INSTRUCTION_AND:
        case INSTRUCTION_OR:
        case INSTRUCTION_XOR:
        case INSTRUCTION_ARRAY_SIZE:
        case INSTRUCTION_PREPEND_ARRAY:
        case INSTRUCTION_APPEND_ARRAY:
        case INSTRUCTION_GET_FIRST:
        case INSTRUCTION_GET_LAST:
        case INSTRUCTION_REMOVE_FIRST:
        case INSTRUCTION_REMOVE_LAST:
        case INSTRUCTION_MOVE_TO_INDEX:
        case INSTRUCTION_MOVE_TO_FIRST:
        default:
            *instruction_pointer += 1;
            break;
    }

    return instruction_ok;
}

/* Stores an integer in a bank.
 * INT BANK LITERAL 
 */
bool instruction_integer(Program *program, Instruction *instruction, int *instruction_pointer)
{
    bool ok;
    int identifier = instruction->parameters.first.integer;
    Bank *bank = new_bank(identifier);
    int integer_value = string_to_integer(instruction->parameters.second.string, &ok);

    if (ok)
    {
        bool set_bank = set_bank_integer(bank, integer_value);
        if (set_bank)
        {
            bool added_bank = append_bank_to_program(program, bank);
            if (!added_bank)
            {
                free_bank(bank);
            }
        }
    }
    else
    {
        free_bank(bank);
    }
    
    *instruction_pointer += 1;
}