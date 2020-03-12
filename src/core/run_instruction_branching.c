#include "headers/run_instruction_branching.h"
#include "headers/logging.h"

bool instruction_jump_label(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    bool instruction_ok = false;
    int target_label = parameters->first.integer;

    // Find the instruction with the label.
    InstructionPointer new_instruction_pointer = get_label_instruction_pointer(program, target_label);
    
    // Found instruction. Jumping to it.
    if (new_instruction_pointer >= 0)
    {
        log_debug("Jumping to instruction %02i.\n", new_instruction_pointer + 1);
        *instruction_pointer = new_instruction_pointer + 1;
        instruction_ok = true;
    }

    // Did not find instruction. Going to next.
    else
    {
        log_debug("Jumping to non-existent label. Going to next instruction.\n");
        *instruction_pointer += 1;
        instruction_ok = false;
    }
    
    return instruction_ok;
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
