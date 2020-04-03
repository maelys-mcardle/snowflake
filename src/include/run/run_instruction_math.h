#ifndef SNOWFLAKE_RUN_INSTRUCTION_MATH_H
#define SNOWFLAKE_RUN_INSTRUCTION_MATH_H
#include <stdbool.h>
#include "core/program.h"
#include "core/instructions.h"

bool instruction_add(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);
bool instruction_subtract(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);
bool instruction_multiply(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);
bool instruction_divide(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);
bool instruction_modulo(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);
bool instruction_power(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);
bool instruction_square_root(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);
bool instruction_increment(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);
bool instruction_decrement(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);
bool add_value(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer, int value_to_add);

#endif