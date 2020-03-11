#ifndef SNOWFLAKE_RUN_INSTRUCTION_BASIC_H
#define SNOWFLAKE_RUN_INSTRUCTION_BASIC_H
#include <stdbool.h>
#include "program.h"
#include "instructions.h"

bool instruction_noop(Program *program, Parameters *parameters, int *instruction_pointer);
bool instruction_output(Program *program, Parameters *parameters, int *instruction_pointer);
bool instruction_input(Program *program, Parameters *parameters, int *instruction_pointer);
bool instruction_delete(Program *program, Parameters *parameters, int *instruction_pointer);
bool instruction_type(Program *program, Parameters *parameters, int *instruction_pointer);
bool instruction_copy(Program *program, Parameters *parameters, int *instruction_pointer);
bool instruction_convert(Program *program, Parameters *parameters, int *instruction_pointer);
bool instruction_length(Program *program, Parameters *parameters, int *instruction_pointer);

#endif