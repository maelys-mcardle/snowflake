#ifndef SNOWFLAKE_RUN_INSTRUCTION_LOGIC_H
#define SNOWFLAKE_RUN_INSTRUCTION_LOGIC_H
#include <stdbool.h>
#include "core/program.h"
#include "core/instructions.h"

bool instruction_not(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);
bool instruction_and(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);
bool instruction_or(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);
bool instruction_xor(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);

#endif