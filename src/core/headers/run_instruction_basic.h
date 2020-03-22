#ifndef SNOWFLAKE_RUN_INSTRUCTION_BASIC_H
#define SNOWFLAKE_RUN_INSTRUCTION_BASIC_H
#include <stdbool.h>
#include "structures/program.h"
#include "structures/instructions.h"

bool instruction_noop(Program *program, Parameters *parameters, InstructionIndex *instruction_pointer);
bool instruction_output(Program *program, Parameters *parameters, InstructionIndex *instruction_pointer);
bool instruction_input(Program *program, Parameters *parameters, InstructionIndex *instruction_pointer);
bool instruction_delete(Program *program, Parameters *parameters, InstructionIndex *instruction_pointer);
bool instruction_type(Program *program, Parameters *parameters, InstructionIndex *instruction_pointer);
bool instruction_copy(Program *program, Parameters *parameters, InstructionIndex *instruction_pointer);
bool instruction_convert(Program *program, Parameters *parameters, InstructionIndex *instruction_pointer);
bool instruction_length(Program *program, Parameters *parameters, InstructionIndex *instruction_pointer);

#endif