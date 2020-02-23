#ifndef SNOWFLAKE_RUN_PROGRAM_H
#define SNOWFLAKE_RUN_PROGRAM_H
#include <stdbool.h>
#include "program.h"
#include "instructions.h"

void run_program(Program *program);
bool run_instruction(Program *program, Instruction *instruction, int *instruction_pointer);
bool instruction_integer(Program *program, Instruction *instruction, int *instruction_pointer);

#endif