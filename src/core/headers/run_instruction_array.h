#ifndef SNOWFLAKE_RUN_INSTRUCTION_ARRAY_H
#define SNOWFLAKE_RUN_INSTRUCTION_ARRAY_H
#include <stdbool.h>
#include "structures/program.h"
#include "structures/instructions.h"

bool instruction_bank_to_first(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);
bool instruction_bank_to_last(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);
bool instruction_first_to_bank(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);
bool instruction_last_to_bank(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);
bool instruction_first_to_index(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);
bool instruction_last_to_index(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);
bool instruction_index_to_first(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);
bool instruction_index_to_last(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);

#endif