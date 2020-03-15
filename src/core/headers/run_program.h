#ifndef SNOWFLAKE_RUN_PROGRAM_H
#define SNOWFLAKE_RUN_PROGRAM_H
#include <stdbool.h>
#include "program.h"
#include "instructions.h"

typedef bool (*InstructionFunction)(Program *, Parameters *, InstructionIndex *);

void run_program(Program *program);
bool run_instruction(Program *program, Instruction *instruction, InstructionIndex *instruction_pointer);

#endif