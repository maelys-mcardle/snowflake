#ifndef SNOWFLAKE_RUN_INSTRUCTION_H
#define SNOWFLAKE_RUN_INSTRUCTION_H
#include <stdbool.h>
#include "program.h"
#include "instructions.h"

bool instruction_integer(Program *program, Instruction *instruction, int *instruction_pointer);
bool instruction_float(Program *program, Instruction *instruction, int *instruction_pointer);
bool instruction_string(Program *program, Instruction *instruction, int *instruction_pointer);
Bank *new_bank_with_identifier(Instruction *instruction);

#endif