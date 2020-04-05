#ifndef SNOWFLAKE_PRINT_INSTRUCTION_H
#define SNOWFLAKE_PRINT_INSTRUCTION_H
#include <stdbool.h>
#include "core/program.h"
#include "core/instructions.h"

#define MAX_IDENTIFIER_SIZE 12

char *get_printable_instruction(Program *program, Instruction *instruction);
char *get_printable_parameter(Program *program, InstructionCode current_instruction, ParameterType type, ParameterValue value);
char *get_printable_identifier(Program *program, InstructionCode current_instruction, InstructionCode naming_instruction, int target_identifier, char *format);
char *get_printable_device(int device);
char *get_printable_type(int type);
char *get_name(Program *program, InstructionCode naming_instruction, int target_identifier);

#endif