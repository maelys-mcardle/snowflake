#include <stdlib.h>
#include "headers/run_program.h"
#include "headers/run_instruction_array.h"
#include "headers/run_instruction_basic.h"
#include "headers/run_instruction_branching.h"
#include "headers/run_instruction_logic.h"
#include "headers/run_instruction_math.h"
#include "headers/run_instruction_types.h"
#include "headers/input_devices.h"
#include "headers/output_devices.h"
#include "headers/bank.h"
#include "headers/errors.h"
#include "headers/logging.h"

InstructionFunction all_instruction_functions[] = {
    [INSTRUCTION_COMMENT]             = &instruction_noop,
    [INSTRUCTION_LABEL]               = &instruction_noop,
    [INSTRUCTION_NAME_BANK]           = &instruction_noop,
    [INSTRUCTION_OUTPUT]              = &instruction_output,
    [INSTRUCTION_INPUT]               = &instruction_input,
    [INSTRUCTION_COPY]                = &instruction_copy,
    [INSTRUCTION_CONVERT]             = &instruction_convert,
    [INSTRUCTION_TYPE]                = &instruction_type,
    [INSTRUCTION_DELETE]              = &instruction_delete,
    [INSTRUCTION_LENGTH]              = &instruction_length,
    [INSTRUCTION_VARIABLE]            = &instruction_variable,
    [INSTRUCTION_BOOLEAN]             = &instruction_boolean,
    [INSTRUCTION_INTEGER]             = &instruction_integer,
    [INSTRUCTION_FLOAT]               = &instruction_float,
    [INSTRUCTION_STRING]              = &instruction_string,
    [INSTRUCTION_ARRAY]               = &instruction_array,
    [INSTRUCTION_JUMP_LABEL]          = &instruction_noop,
    [INSTRUCTION_JUMP_BANK]           = &instruction_noop,
    [INSTRUCTION_IF_EQUAL]            = &instruction_noop,
    [INSTRUCTION_IF_NOT_EQUAL]        = &instruction_noop,
    [INSTRUCTION_IF_GREATER_THAN]     = &instruction_noop,
    [INSTRUCTION_IF_LESSER_THAN]      = &instruction_noop,
    [INSTRUCTION_ADD]                 = &instruction_add,
    [INSTRUCTION_SUBTRACT]            = &instruction_subtract,
    [INSTRUCTION_MULTIPLY]            = &instruction_multiply,
    [INSTRUCTION_DIVIDE]              = &instruction_divide,
    [INSTRUCTION_MODULO]              = &instruction_modulo,
    [INSTRUCTION_POWER]               = &instruction_power,
    [INSTRUCTION_SQUARE_ROOT]         = &instruction_square_root,
    [INSTRUCTION_NOT]                 = &instruction_noop,
    [INSTRUCTION_AND]                 = &instruction_noop,
    [INSTRUCTION_OR]                  = &instruction_noop,
    [INSTRUCTION_XOR]                 = &instruction_noop,
    [INSTRUCTION_PREPEND_ARRAY]       = &instruction_noop,
    [INSTRUCTION_APPEND_ARRAY]        = &instruction_noop,
    [INSTRUCTION_GET_FIRST]           = &instruction_noop,
    [INSTRUCTION_GET_LAST]            = &instruction_noop,
    [INSTRUCTION_REMOVE_FIRST]        = &instruction_noop,
    [INSTRUCTION_REMOVE_LAST]         = &instruction_noop,
    [INSTRUCTION_MOVE_FIRST_TO_INDEX] = &instruction_noop,
    [INSTRUCTION_MOVE_LAST_TO_INDEX]  = &instruction_noop,
    [INSTRUCTION_MOVE_TO_FIRST]       = &instruction_noop,
    [INSTRUCTION_MOVE_TO_LAST]        = &instruction_noop,
};

void run_program(Program *program)
{
    log_debug("Executing program...\n");

    if (program != NULL && 
        program->instructions.instructions != NULL && 
        program->instructions.count > 0)
    {
        initialize_input();
        initialize_output();

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
            "Instruction Code: %02i\n"
            "Instruction Mnemonic: '%c%c%c'\n",
            *instruction_pointer,
            instruction->instruction,
            info.mnemonic[0],
            info.mnemonic[1],
            info.mnemonic[2]);
    }

    // Get the instruction to execute.
    InstructionCode instruction_code = instruction->instruction;
    InstructionFunction execute_intruction = all_instruction_functions[instruction_code];

    // Execute the command.
    Parameters *parameters = &(instruction->parameters);
    bool instruction_ok = execute_intruction(program, parameters, instruction_pointer);

    return instruction_ok;
}
