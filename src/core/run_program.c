#include <stdlib.h>
#include "headers/run_program.h"
#include "headers/run_instruction_array.h"
#include "headers/run_instruction_basic.h"
#include "headers/run_instruction_branching.h"
#include "headers/run_instruction_logic.h"
#include "headers/run_instruction_math.h"
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
    if (is_debug_mode())
    {
        bool instruction_exists = false;
        InstructionInfo info = get_instruction_info(
            instruction->instruction, &instruction_exists);
        
        log_debug("[Executing Instruction %02i]\n"
            "Instruction Code: %02i\n",
            *instruction_pointer,
            instruction->instruction);
        
        if (instruction_exists)
        {
            log_debug("Instruction Mnemonic: '%c%c%c'\n",
                info.mnemonic[0],
                info.mnemonic[1],
                info.mnemonic[2]);
        }
    }

    bool instruction_ok = true;
    Parameters *parameters = &(instruction->parameters);
    switch (instruction->instruction)
    {
        case INSTRUCTION_COMMENT:
        case INSTRUCTION_LABEL:
        case INSTRUCTION_NAME_BANK:
            instruction_ok = instruction_noop(program, parameters, instruction_pointer);
            break;
        case INSTRUCTION_OUTPUT:
            instruction_ok = instruction_output(program, parameters, instruction_pointer);
            break;
        case INSTRUCTION_INPUT:
            instruction_ok = instruction_input(program, parameters, instruction_pointer);
            break;
        case INSTRUCTION_COPY:
            instruction_ok = instruction_copy(program, parameters, instruction_pointer);
            break;
        case INSTRUCTION_CONVERT:
            instruction_ok = instruction_convert(program, parameters, instruction_pointer);
            break;
        case INSTRUCTION_TYPE:
            instruction_ok = instruction_type(program, parameters, instruction_pointer);
            break;
        case INSTRUCTION_DELETE:
            instruction_ok = instruction_delete(program, parameters, instruction_pointer);
            break;
        case INSTRUCTION_LENGTH:
            instruction_ok = instruction_length(program, parameters, instruction_pointer);
            break;
        case INSTRUCTION_VARIABLE:
            instruction_ok = instruction_variable(program, parameters, instruction_pointer);
            break;
        case INSTRUCTION_BOOLEAN:
            instruction_ok = instruction_boolean(program, parameters, instruction_pointer);
            break;
        case INSTRUCTION_INTEGER:
            instruction_ok = instruction_integer(program, parameters, instruction_pointer);
            break;
        case INSTRUCTION_FLOAT:
            instruction_ok = instruction_float(program, parameters, instruction_pointer);
            break;
        case INSTRUCTION_STRING:
            instruction_ok = instruction_string(program, parameters, instruction_pointer);
            break;
        case INSTRUCTION_ARRAY:
            instruction_ok = instruction_array(program, parameters, instruction_pointer);
            break;
        case INSTRUCTION_JUMP_LABEL:
        case INSTRUCTION_JUMP_BANK:
        case INSTRUCTION_IF_EQUAL:
        case INSTRUCTION_IF_NOT_EQUAL:
        case INSTRUCTION_IF_GREATER_THAN:
        case INSTRUCTION_IF_LESSER_THAN:
            *instruction_pointer += 1;
            break;
        case INSTRUCTION_ADD:
            instruction_ok = instruction_add(program, parameters, instruction_pointer);
            break;
        case INSTRUCTION_SUBTRACT:
            instruction_ok = instruction_subtract(program, parameters, instruction_pointer);
            break;
        case INSTRUCTION_MULTIPLY:
            instruction_ok = instruction_multiply(program, parameters, instruction_pointer);
            break;
        case INSTRUCTION_DIVIDE:
            instruction_ok = instruction_divide(program, parameters, instruction_pointer);
            break;
        case INSTRUCTION_MODULO:
            instruction_ok = instruction_modulo(program, parameters, instruction_pointer);
            break;
        case INSTRUCTION_POWER:
            instruction_ok = instruction_power(program, parameters, instruction_pointer);
            break;
        case INSTRUCTION_SQUARE_ROOT:
            instruction_ok = instruction_square_root(program, parameters, instruction_pointer);
            break;
        case INSTRUCTION_NOT:
        case INSTRUCTION_AND:
        case INSTRUCTION_OR:
        case INSTRUCTION_XOR:
        case INSTRUCTION_PREPEND_ARRAY:
        case INSTRUCTION_APPEND_ARRAY:
        case INSTRUCTION_GET_FIRST:
        case INSTRUCTION_GET_LAST:
        case INSTRUCTION_REMOVE_FIRST:
        case INSTRUCTION_REMOVE_LAST:
        case INSTRUCTION_MOVE_FIRST_TO_INDEX:
        case INSTRUCTION_MOVE_LAST_TO_INDEX:
        case INSTRUCTION_MOVE_TO_FIRST:
        case INSTRUCTION_MOVE_TO_LAST:
            *instruction_pointer += 1;
            break;
        default:
            log_error(ERROR_MESG_UNRECOGNIZED_INSTRUCTION, 
                instruction->instruction);
            instruction_noop(program, parameters, instruction_pointer);
            instruction_ok = false;
            break;
    }

    return instruction_ok;
}
