#include <stdlib.h>
#include <math.h>
#include "run/run_instruction_math.h"
#include "core/string.h"
#include "platforms/logging.h"
#include "run/bank_operations.h"
#include "errors.h"

/**
 * Implement + instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_add(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    return dual_bank_operation(
        program, parameters, instruction_pointer, bank_operation_addition, "Addition");
}

/**
 * Implement - instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_subtract(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    return dual_bank_operation(
        program, parameters, instruction_pointer, bank_operation_subtraction, "Subtraction");
}

/**
 * Implement * instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_multiply(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    return dual_bank_operation(
        program, parameters, instruction_pointer, bank_operation_multiplication, "Multiplication");
}

/**
 * Implement / instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_divide(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    return dual_bank_operation(
        program, parameters, instruction_pointer, bank_operation_division, "Division");
}

/**
 * Implement % instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_modulo(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    return dual_bank_operation(
        program, parameters, instruction_pointer, bank_operation_modulo, "Modulo");
}

/**
 * Implement ** instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_power(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    return dual_bank_operation(
        program, parameters, instruction_pointer, bank_operation_power, "Power");
}

/**
 * Implement SQR instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_square_root(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    return single_bank_operation(
        program, parameters, instruction_pointer, bank_operation_square_root, "Square Root");
}

/**
 * Implement +1 instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_increment(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    return add_value(program, parameters, instruction_pointer, 1);
}

/**
 * Implement -1 instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_decrement(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    return add_value(program, parameters, instruction_pointer, -1);
}

bool add_value(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer, int value_to_add)
{
    Bank *bank = get_bank_from_parameter(program, &(parameters->first));
    bool instruction_ok = false;

    if (bank != NULL)
    {
        log_debug("Adding %i to Bank %02i.\n", 
            value_to_add, bank->identifier);

        Bank *add_value_bank = new_bank(0);

        if (add_value_bank != NULL)
        {
            set_bank_integer(add_value_bank, value_to_add);

            instruction_ok = bank_operation_addition(
                bank, add_value_bank, "Increment/Decrement");
        
            free_bank(add_value_bank);
         }
    }
    else
    {
        log_error(ERROR_MESG_IGNORING_OPERATION_BANK_UNDEFINED, 
            "increment/decrement", parameters->first.identifier);
    }

    increment_instruction(instruction_pointer);
    return instruction_ok;
}
