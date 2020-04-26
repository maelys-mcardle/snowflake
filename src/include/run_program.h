#ifndef SNOWFLAKE_RUN_PROGRAM_H
#define SNOWFLAKE_RUN_PROGRAM_H
#include <stdbool.h>
#include "core/program.h"
#include "core/instructions.h"

typedef bool (*InstructionFunction)(Program *, Parameters *, InstructionPointer *);

int run_program(Program *program);
bool run_instruction(Program *program, Instruction *instruction, InstructionPointer *instruction_pointer);

#endif