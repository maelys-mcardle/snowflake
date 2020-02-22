#ifndef SNOWFLAKE_RUN_PROGRAM_H
#define SNOWFLAKE_RUN_PROGRAM_H
#include <stdbool.h>
#include "program.h"
#include "instructions.h"

void run_program(Program *program);
void run_instruction(Program *program, Instruction *instruction);

#endif