#include <stdlib.h>
#include "run/run_instruction_array.h"
#include "run/run_instruction_basic.h"
#include "run/run_instruction_branching.h"
#include "run/run_instruction_io.h"
#include "run/run_instruction_logic.h"
#include "run/run_instruction_math.h"
#include "run/run_instruction_types.h"
#include "platforms/input_devices.h"
#include "platforms/output_devices.h"
#include "core/bank.h"
#include "errors.h"
#include "platforms/logging.h"
#include "core/array.h"
#include "run_program.h"

/**
 * All the instructions and the functions to execute them.
 */
InstructionFunction all_instruction_functions[] = {
    [INSTRUCTION_COMMENT]         = &instruction_noop,
    [INSTRUCTION_LABEL]           = &instruction_noop,
    [INSTRUCTION_NAME_BANK]       = &instruction_noop,
    [INSTRUCTION_OUTPUT]          = &instruction_output,
    [INSTRUCTION_INPUT]           = &instruction_input,
    [INSTRUCTION_COPY]            = &instruction_copy,
    [INSTRUCTION_CONVERT]         = &instruction_convert,
    [INSTRUCTION_TYPE]            = &instruction_type,
    [INSTRUCTION_DELETE]          = &instruction_delete,
    [INSTRUCTION_LENGTH]          = &instruction_length,
    [INSTRUCTION_VARIABLE]        = &instruction_variable,
    [INSTRUCTION_BOOLEAN]         = &instruction_boolean,
    [INSTRUCTION_INTEGER]         = &instruction_integer,
    [INSTRUCTION_FLOAT]           = &instruction_float,
    [INSTRUCTION_STRING]          = &instruction_string,
    [INSTRUCTION_ARRAY]           = &instruction_array,
    [INSTRUCTION_JUMP_LABEL]      = &instruction_jump_label,
    [INSTRUCTION_JUMP_BANK]       = &instruction_jump_bank,
    [INSTRUCTION_IF_EQUAL]        = &instruction_if_equal,
    [INSTRUCTION_IF_NOT_EQUAL]    = &instruction_if_not_equal,
    [INSTRUCTION_IF_GREATER_THAN] = &instruction_if_greater_than,
    [INSTRUCTION_IF_LESSER_THAN]  = &instruction_if_lesser_than,
    [INSTRUCTION_ADD]             = &instruction_add,
    [INSTRUCTION_SUBTRACT]        = &instruction_subtract,
    [INSTRUCTION_MULTIPLY]        = &instruction_multiply,
    [INSTRUCTION_DIVIDE]          = &instruction_divide,
    [INSTRUCTION_MODULO]          = &instruction_modulo,
    [INSTRUCTION_POWER]           = &instruction_power,
    [INSTRUCTION_SQUARE_ROOT]     = &instruction_square_root,
    [INSTRUCTION_INCREMENT]       = &instruction_increment,
    [INSTRUCTION_DECREMENT]       = &instruction_decrement,
    [INSTRUCTION_NOT]             = &instruction_not,
    [INSTRUCTION_AND]             = &instruction_and,
    [INSTRUCTION_OR]              = &instruction_or,
    [INSTRUCTION_XOR]             = &instruction_xor,
    [INSTRUCTION_BANK_TO_FIRST]   = &instruction_bank_to_first,
    [INSTRUCTION_BANK_TO_LAST]    = &instruction_bank_to_last,
    [INSTRUCTION_FIRST_TO_BANK]   = &instruction_first_to_bank,
    [INSTRUCTION_LAST_TO_BANK]    = &instruction_last_to_bank,
    [INSTRUCTION_FIRST_TO_INDEX]  = &instruction_first_to_index,
    [INSTRUCTION_LAST_TO_INDEX]   = &instruction_last_to_index,
    [INSTRUCTION_INDEX_TO_FIRST]  = &instruction_index_to_first,
    [INSTRUCTION_INDEX_TO_LAST]   = &instruction_index_to_last
};

/**
 * Executes the snowflake program.
 * 
 * @param program the snowflake program to execute.
 */
int run_program(Program *program)
{
    log_debug("Executing program...\n");
    bool executed_instruction = false;

    if (program != NULL && 
        program->instructions != NULL)
    {
        // Initialize the devices.
        initialize_input_devices();
        initialize_output_devices();

        // Run the program.
        InstructionPointer instruction_pointer = 0;
        while (instruction_pointer < get_instruction_count(program))
        {
            // Fetch the instruction.
            Instruction *instruction = get_instruction(program, instruction_pointer);

            // Run the instruction.
            bool instruction_ok = run_instruction(program, instruction, &instruction_pointer);

            // Note if an instruction was run.
            if (instruction_ok)
            {
                executed_instruction = true;
            }
        }
    }

    if (!executed_instruction)
    {
        log_error(ERROR_MESG_NO_INSTRUCTION_EXECUTED_OK);
        return ERROR_CODE_NO_INSTRUCTION_EXECUTED_OK;
    }

    return SUCCESS;
}

/**
 * Executes an individual instruction.
 * 
 * @param program the snowflake program.
 * @param instruction the instruction to execute.
 * @param instruction_pointer the current instruction pointer.
 * @return whether the instruction executed successfully.
 */
bool run_instruction(Program *program, Instruction *instruction, InstructionPointer *instruction_pointer)
{
    // If this is the debug mode, provide more logging.
    if (is_debug_mode())
    {
        bool instruction_exists = false;
        InstructionInfo info = get_instruction_info(
            instruction->instruction, &instruction_exists);

        log_debug("[Executing Instruction %02i]\n"
            "Instruction Code: %02i\n"
            "Instruction Mnemonic: '%s'\n",
            *instruction_pointer,
            instruction->instruction,
            info.mnemonic);
    }

    // Get the instruction to execute.
    InstructionCode instruction_code = instruction->instruction;
    InstructionFunction execute_intruction = all_instruction_functions[instruction_code];

    // Execute the command.
    Parameters *parameters = &(instruction->parameters);
    bool instruction_ok = execute_intruction(program, parameters, instruction_pointer);

    return instruction_ok;
}
