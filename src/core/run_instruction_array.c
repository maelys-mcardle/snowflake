#include "platforms/logging.h"
#include "run_instruction_array.h"

bool instruction_bank_to_first(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    // Unused parameters. This is done to suppress compiler warnings.
    (void)(program);
    (void)(parameters);

    // Perform no-op.
    bool instruction_ok = true;
    log_debug("No-op instruction.\n");
    increment_instruction(instruction_pointer);
    return instruction_ok;
}

bool instruction_bank_to_last(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    // Unused parameters. This is done to suppress compiler warnings.
    (void)(program);
    (void)(parameters);

    // Perform no-op.
    bool instruction_ok = true;
    log_debug("No-op instruction.\n");
    increment_instruction(instruction_pointer);
    return instruction_ok;
}

bool instruction_first_to_bank(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    // Unused parameters. This is done to suppress compiler warnings.
    (void)(program);
    (void)(parameters);

    // Perform no-op.
    bool instruction_ok = true;
    log_debug("No-op instruction.\n");
    increment_instruction(instruction_pointer);
    return instruction_ok;
}

bool instruction_last_to_bank(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    // Unused parameters. This is done to suppress compiler warnings.
    (void)(program);
    (void)(parameters);

    // Perform no-op.
    bool instruction_ok = true;
    log_debug("No-op instruction.\n");
    increment_instruction(instruction_pointer);
    return instruction_ok;
}

bool instruction_first_to_index(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    // Unused parameters. This is done to suppress compiler warnings.
    (void)(program);
    (void)(parameters);

    // Perform no-op.
    bool instruction_ok = true;
    log_debug("No-op instruction.\n");
    increment_instruction(instruction_pointer);
    return instruction_ok;
}

bool instruction_last_to_index(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    // Unused parameters. This is done to suppress compiler warnings.
    (void)(program);
    (void)(parameters);

    // Perform no-op.
    bool instruction_ok = true;
    log_debug("No-op instruction.\n");
    increment_instruction(instruction_pointer);
    return instruction_ok;
}

bool instruction_index_to_first(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    // Unused parameters. This is done to suppress compiler warnings.
    (void)(program);
    (void)(parameters);

    // Perform no-op.
    bool instruction_ok = true;
    log_debug("No-op instruction.\n");
    increment_instruction(instruction_pointer);
    return instruction_ok;
}

bool instruction_index_to_last(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    // Unused parameters. This is done to suppress compiler warnings.
    (void)(program);
    (void)(parameters);

    // Perform no-op.
    bool instruction_ok = true;
    log_debug("No-op instruction.\n");
    increment_instruction(instruction_pointer);
    return instruction_ok;
}

