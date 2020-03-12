#ifndef SNOWFLAKE_RUN_INSTRUCTION_BRANCHING_H
#define SNOWFLAKE_RUN_INSTRUCTION_BRANCHING_H
#include <stdbool.h>
#include "program.h"
#include "instructions.h"

bool instruction_jump_label(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);
InstructionPointer get_label_instruction_pointer(Program *program, int target_label);

#endif