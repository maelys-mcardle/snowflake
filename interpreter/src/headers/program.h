#ifndef SNOWFLAKE_PROGRAM_H
#define SNOWFLAKE_PROGRAM_H
#include <stdbool.h>
#include "instructions.h"
#include "bank.h"

typedef struct {
    int count;
    Bank **banks;
} ProgramBanks;

typedef struct {
    int count;
    Instruction **instructions;
} ProgramInstructions;

typedef struct {
    ProgramBanks banks;
    ProgramInstructions instructions;
} Program;

Program *new_program();
void free_program(Program *program);
bool append_instruction_to_program(Program *program, Instruction *instruction);

#endif
