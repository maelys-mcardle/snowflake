#ifndef SNOWFLAKE_INSTRUCTIONS_H
#define SNOWFLAKE_INSTRUCTIONS_H
#include <stdbool.h>
#include "instruction_info.h"
#include "devices.h"
#include "parameters.h"
#include "bank.h"

typedef struct {
    ParameterValue first;
    ParameterValue second;
} Parameters;

typedef struct {
    InstructionCode instruction;
    Parameters parameters;
} Instruction;

Instruction *new_instruction();
void free_instruction(void *instruction);

#endif
