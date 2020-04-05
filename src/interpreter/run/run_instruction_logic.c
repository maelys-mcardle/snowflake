#include <stdlib.h>
#include "run/run_instruction_logic.h"
#include "platforms/logging.h"
#include "run/bank_operations.h"
#include "errors.h"

/**
 * Implement ! instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_not(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    return single_bank_operation(
        program, parameters, instruction_pointer, bank_operation_not, "Logical NOT");
}

/**
 * Implement & instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_and(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    return dual_bank_operation(
        program, parameters, instruction_pointer, bank_operation_and, "Logical AND");
}

/**
 * Implement | instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_or(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    return dual_bank_operation(
        program, parameters, instruction_pointer, bank_operation_or, "Logical OR");
}

/**
 * Implement ^ instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_xor(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    return dual_bank_operation(
        program, parameters, instruction_pointer, bank_operation_xor, "Logical XOR");
}