#ifndef SNOWFLAKE_RUN_INSTRUCTION_ARRAY_H
#define SNOWFLAKE_RUN_INSTRUCTION_ARRAY_H
#include <stdbool.h>
#include "structures/program.h"
#include "structures/instructions.h"

typedef enum {
    FIRST,
    LAST,
    INDEX
} ArrayPosition;

bool instruction_bank_to_first(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);
bool instruction_bank_to_last(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);
bool instruction_first_to_bank(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);
bool instruction_last_to_bank(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);
bool instruction_first_to_index(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);
bool instruction_last_to_index(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);
bool instruction_index_to_first(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);
bool instruction_index_to_last(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);

bool bank_to_array(Program *program, Parameters *parameters, ArrayPosition position);
bool array_to_bank(Program *program, Parameters *parameters, ArrayPosition position);
bool array_shift_positions(Program *program, Parameters *parameters, ArrayPosition from, ArrayPosition to);
ArrayIndex get_array_index_from_position(ArrayPosition position, Array *array, ArrayIndex index);
#endif