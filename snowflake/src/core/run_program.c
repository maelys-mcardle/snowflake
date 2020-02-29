#include <stdlib.h>
#include "headers/run_program.h"
#include "headers/run_instruction_basic.h"
#include "headers/run_instruction_types.h"
#include "headers/output.h"
#include "headers/bank.h"
#include "headers/errors.h"

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
    log_debug("[Executing %02i] Instruction: %c%c%c\n",
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
            instruction_ok = instruction_noop(program, instruction, instruction_pointer);
            break;
        case INSTRUCTION_OUTPUT:
            instruction_ok = instruction_output(program, instruction, instruction_pointer);
            break;
        case INSTRUCTION_INPUT:
            instruction_ok = instruction_input(program, instruction, instruction_pointer);
            break;
        case INSTRUCTION_COPY:
            *instruction_pointer += 1;
            break;
        case INSTRUCTION_DELETE:
            instruction_ok = instruction_delete(program, instruction, instruction_pointer);
            break;
        case INSTRUCTION_TYPE:
            *instruction_pointer += 1;
            break;
        case INSTRUCTION_VARIABLE:
            instruction_ok = instruction_variable(program, instruction, instruction_pointer);
            break;
        case INSTRUCTION_BOOLEAN:
            instruction_ok = instruction_boolean(program, instruction, instruction_pointer);
            break;
        case INSTRUCTION_INTEGER:
            instruction_ok = instruction_integer(program, instruction, instruction_pointer);
            break;
        case INSTRUCTION_FLOAT:
            instruction_ok = instruction_float(program, instruction, instruction_pointer);
            break;
        case INSTRUCTION_STRING:
            instruction_ok = instruction_string(program, instruction, instruction_pointer);
            break;
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
            *instruction_pointer += 1;
            break;
        default:
            log_error(ERROR_MESG_UNRECOGNIZED_INSTRUCTION, 
                instruction->instruction);
            instruction_noop(program, instruction, instruction_pointer);
            instruction_ok = false;
            break;
    }

    return instruction_ok;
}
