#ifndef SNOWFLAKE_RUN_INSTRUCTION_TYPES_H
#define SNOWFLAKE_RUN_INSTRUCTION_TYPES_H
#include <stdbool.h>
#include "structures/program.h"
#include "structures/instructions.h"

bool instruction_variable(Program *program, Parameters *parameters, InstructionIndex *instruction_pointer);
bool instruction_boolean(Program *program, Parameters *parameters, InstructionIndex *instruction_pointer);
bool instruction_integer(Program *program, Parameters *parameters, InstructionIndex *instruction_pointer);
bool instruction_float(Program *program, Parameters *parameters, InstructionIndex *instruction_pointer);
bool instruction_string(Program *program, Parameters *parameters, InstructionIndex *instruction_pointer);
bool instruction_array(Program *program, Parameters *parameters, InstructionIndex *instruction_pointer);

#endif