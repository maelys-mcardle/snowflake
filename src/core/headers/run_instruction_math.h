#ifndef SNOWFLAKE_RUN_INSTRUCTION_MATH_H
#define SNOWFLAKE_RUN_INSTRUCTION_MATH_H
#include <stdbool.h>
#include "program.h"
#include "instructions.h"

bool instruction_add(Program *program, Instruction *instruction, int *instruction_pointer);
bool instruction_subtract(Program *program, Instruction *instruction, int *instruction_pointer);
bool instruction_multiply(Program *program, Instruction *instruction, int *instruction_pointer);
bool instruction_divide(Program *program, Instruction *instruction, int *instruction_pointer);
bool instruction_modulo(Program *program, Instruction *instruction, int *instruction_pointer);
bool instruction_power(Program *program, Instruction *instruction, int *instruction_pointer);
bool instruction_square_root(Program *program, Instruction *instruction, int *instruction_pointer);

#endif