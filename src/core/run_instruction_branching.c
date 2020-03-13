#include "headers/run_instruction_branching.h"
#include "headers/logging.h"

bool instruction_jump_label(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    int target_label = parameters->first.integer;
    bool instruction_ok = jump_to_label(program, instruction_pointer, target_label);
    return instruction_ok;
}

bool instruction_jump_bank(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    bool found_label = false;
    Bank *bank = get_bank_from_parameter(program, &(parameters->first));

    if (bank != NULL)
    {
        int target_label = get_bank_as_integer(bank);
        found_label = jump_to_label(program, instruction_pointer, target_label);
    }
    else
    {
        log_debug("Bank was not defined for jump. Going to next instruction.\n");
        *instruction_pointer += 1;
    }
    
    return found_label;
}

bool jump_to_label(Program *program, InstructionPointer *instruction_pointer, int target_label)
{
    // Find the instruction with the label.
    InstructionPointer new_instruction_pointer = get_label_instruction_pointer(program, target_label);
    
    // Found instruction. Jumping to it.
    if (new_instruction_pointer >= 0)
    {
        log_debug("Jumping to instruction %02i.\n", new_instruction_pointer + 1);
        *instruction_pointer = new_instruction_pointer + 1;
        return true;
    }

    // Did not find instruction. Going to next.
    else
    {
        log_debug("Jumping to non-existent label. Going to next instruction.\n");
        *instruction_pointer += 1;
        return false;
    }
}

InstructionPointer get_label_instruction_pointer(Program *program, int target_label)
{
    for (int index = 0; index < program->instructions.count; index++)
    {
        Instruction *instruction = program->instructions.instructions[index];
        if (instruction->instruction == INSTRUCTION_LABEL &&
            instruction->parameters.first.integer == target_label)
        {
            return index;
        }
    }

    return -1;
}
