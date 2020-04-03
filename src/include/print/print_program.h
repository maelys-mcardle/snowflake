#ifndef SNOWFLAKE_PRINT_PROGRAM_H
#define SNOWFLAKE_PRINT_PROGRAM_H
#include <stdbool.h>
#include "core/program.h"
#include "core/instructions.h"

#define MAX_IDENTIFIER_SIZE 12

char *get_printable_program(Program *program, bool show_line_number);
char *get_printable_instruction(Program *program, Instruction *instruction);
char *get_printable_parameter(Program *program, InstructionCode current_instruction, ParameterType type, ParameterValue value);
char *get_printable_identifier(Program *program, InstructionCode current_instruction, InstructionCode naming_instruction, int target_identifier, char *format);
char *get_printable_device(int device);
char *get_printable_type(int type);
char *get_name(Program *program, InstructionCode naming_instruction, int target_identifier);
char *get_printable_instruction_line(Program *program, InstructionPointer instruction_pointer, char *line_number_format);
char *get_printable_line_number_format(InstructionCount total_lines);
char *get_printable_line_number(char *string_format, InstructionCount current_line);

#endif