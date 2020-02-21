#ifndef SNOWFLAKE_PROGRAM_H
#define SNOWFLAKE_PROGRAM_H
#include <stdbool.h>
#include "instructions.h"

typedef struct {
    int count;
    Instruction **instructions;
} ProgramInstructions;

typedef struct {
    ProgramInstructions instructions;
} Program;

Program *new_program();
void free_program(Program *program);
bool append_instruction_to_program(Program *program, Instruction *instruction);
void print_program(Program *program);

#endif
