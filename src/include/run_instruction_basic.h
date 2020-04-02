#ifndef SNOWFLAKE_RUN_INSTRUCTION_BASIC_H
#define SNOWFLAKE_RUN_INSTRUCTION_BASIC_H
#include <stdbool.h>
#include "core/program.h"
#include "core/instructions.h"

bool instruction_noop(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);
bool instruction_delete(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);
bool instruction_type(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);
bool instruction_copy(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);
bool instruction_convert(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);
bool instruction_length(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);

#endif