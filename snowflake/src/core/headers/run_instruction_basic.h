#ifndef SNOWFLAKE_RUN_INSTRUCTION_BASIC_H
#define SNOWFLAKE_RUN_INSTRUCTION_BASIC_H
#include <stdbool.h>
#include "program.h"
#include "instructions.h"

bool instruction_noop(Program *program, Instruction *instruction, int *instruction_pointer);
bool instruction_output(Program *program, Instruction *instruction, int *instruction_pointer);
bool instruction_input(Program *program, Instruction *instruction, int *instruction_pointer);
bool instruction_delete(Program *program, Instruction *instruction, int *instruction_pointer);

#endif