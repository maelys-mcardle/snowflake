#ifndef SNOWFLAKE_PRINT_PROGRAM_H
#define SNOWFLAKE_PRINT_PROGRAM_H
#include <stdbool.h>
#include "program.h"
#include "instructions.h"

void print_program(Program *program);
void print_instruction(Program *program, Instruction *instruction);
bool print_parameter(Program *program, ParameterType type, ParameterValue value);
void print_label(Program *program, int label);
void print_bank(Program *program, int bank);
bool print_device(int device);
char *get_name(Program *program, int target_instruction, int target_identifier);

#endif