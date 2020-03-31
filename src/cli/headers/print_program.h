#ifndef SNOWFLAKE_PRINT_PROGRAM_H
#define SNOWFLAKE_PRINT_PROGRAM_H
#include <stdbool.h>
#include "structures/program.h"
#include "structures/instructions.h"

#define MAX_IDENTIFIER_SIZE 12

char *print_program(Program *program);
char *print_instruction(Program *program, Instruction *instruction);
char *print_parameter(Program *program, InstructionCode current_instruction, ParameterType type, ParameterValue value);
char *print_identifier(Program *program, InstructionCode current_instruction, InstructionCode naming_instruction, int target_identifier, char *format);
char *print_device(int device);
char *print_type(int type);
char *get_name(Program *program, InstructionCode naming_instruction, int target_identifier);

#endif