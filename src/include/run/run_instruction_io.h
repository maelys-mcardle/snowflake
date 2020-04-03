#ifndef SNOWFLAKE_RUN_INSTRUCTION_IO_H
#define SNOWFLAKE_RUN_INSTRUCTION_IO_H
#include <stdbool.h>
#include "core/program.h"
#include "core/instructions.h"

bool instruction_output(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);
bool instruction_input(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);

#endif