#ifndef SNOWFLAKE_RUN_INSTRUCTION_BRANCHING_H
#define SNOWFLAKE_RUN_INSTRUCTION_BRANCHING_H
#include <stdbool.h>
#include "structures/program.h"
#include "structures/instructions.h"

bool instruction_jump_label(Program *program, Parameters *parameters, InstructionIndex *instruction_pointer);
bool instruction_jump_bank(Program *program, Parameters *parameters, InstructionIndex *instruction_pointer);
bool instruction_if_equal(Program *program, Parameters *parameters, InstructionIndex *instruction_pointer);
bool instruction_if_not_equal(Program *program, Parameters *parameters, InstructionIndex *instruction_pointer);
bool instruction_if_greater_than(Program *program, Parameters *parameters, InstructionIndex *instruction_pointer);
bool instruction_if_lesser_than(Program *program, Parameters *parameters, InstructionIndex *instruction_pointer);
bool jump_to_label(Program *program, InstructionIndex *instruction_pointer, int target_label);
InstructionIndex get_label_instruction_pointer(Program *program, int target_label, bool *target_found);
bool is_parameters_equal(Program *program, Parameters *parameters);
bool is_string_equal(Bank *first_bank, Bank *second_bank);

#endif