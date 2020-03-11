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
    // If this is the debug mode, provide more logging.
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

    // Get the instruction to execute.
    bool (*execute_intruction)(Program *, Parameters *, int *) = NULL;
    switch (instruction->instruction)
    {
        case INSTRUCTION_COMMENT:
        case INSTRUCTION_LABEL:
        case INSTRUCTION_NAME_BANK:
            execute_intruction = &instruction_noop;
            break;
        case INSTRUCTION_OUTPUT:
            execute_intruction = &instruction_output;
            break;
        case INSTRUCTION_INPUT:
            execute_intruction = &instruction_input;
            break;
        case INSTRUCTION_COPY:
            execute_intruction = &instruction_copy;
            break;
        case INSTRUCTION_CONVERT:
            execute_intruction = &instruction_convert;
            break;
        case INSTRUCTION_TYPE:
            execute_intruction = &instruction_type;
            break;
        case INSTRUCTION_DELETE:
            execute_intruction = &instruction_delete;
            break;
        case INSTRUCTION_LENGTH:
            execute_intruction = &instruction_length;
            break;
        case INSTRUCTION_VARIABLE:
            execute_intruction = &instruction_variable;
            break;
        case INSTRUCTION_BOOLEAN:
            execute_intruction = &instruction_boolean;
            break;
        case INSTRUCTION_INTEGER:
            execute_intruction = &instruction_integer;
            break;
        case INSTRUCTION_FLOAT:
            execute_intruction = &instruction_float;
            break;
        case INSTRUCTION_STRING:
            execute_intruction = &instruction_string;
            break;
        case INSTRUCTION_ARRAY:
            execute_intruction = &instruction_array;
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
            execute_intruction = &instruction_add;
            break;
        case INSTRUCTION_SUBTRACT:
            execute_intruction = &instruction_subtract;
            break;
        case INSTRUCTION_MULTIPLY:
            execute_intruction = &instruction_multiply;
            break;
        case INSTRUCTION_DIVIDE:
            execute_intruction = &instruction_divide;
            break;
        case INSTRUCTION_MODULO:
            execute_intruction = &instruction_modulo;
            break;
        case INSTRUCTION_POWER:
            execute_intruction = &instruction_power;
            break;
        case INSTRUCTION_SQUARE_ROOT:
            execute_intruction = &instruction_square_root;
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
            break;
    }

    // Execute the command.
    bool instruction_ok = true;
    Parameters *parameters = &(instruction->parameters);
    if (execute_intruction != NULL)
    {
        instruction_ok = execute_intruction(program, parameters, instruction_pointer);
    }
    else
    {
        log_error(ERROR_MESG_UNRECOGNIZED_INSTRUCTION, 
                instruction->instruction);
        instruction_noop(program, parameters, instruction_pointer);
        instruction_ok = false;
    }

    return instruction_ok;
}
