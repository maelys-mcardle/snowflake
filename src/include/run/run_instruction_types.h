#ifndef SNOWFLAKE_RUN_INSTRUCTION_TYPES_H
#define SNOWFLAKE_RUN_INSTRUCTION_TYPES_H
#include <stdbool.h>
#include "core/program.h"
#include "core/instructions.h"

bool instruction_variable(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);
bool instruction_boolean(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);
bool instruction_integer(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);
bool instruction_float(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);
bool instruction_string(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);
bool instruction_array(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);

#endif