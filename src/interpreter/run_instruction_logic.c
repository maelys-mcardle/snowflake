#include <stdlib.h>
#include "run_instruction_logic.h"
#include "platforms/logging.h"
#include "bank_operations.h"
#include "errors.h"

bool instruction_not(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    return single_bank_operation(
        program, parameters, instruction_pointer, bank_operation_not, "Logical NOT");
}

bool instruction_and(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    return dual_bank_operation(
        program, parameters, instruction_pointer, bank_operation_and, "Logical AND");
}

bool instruction_or(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    return dual_bank_operation(
        program, parameters, instruction_pointer, bank_operation_or, "Logical OR");
}

bool instruction_xor(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    return dual_bank_operation(
        program, parameters, instruction_pointer, bank_operation_xor, "Logical XOR");
}