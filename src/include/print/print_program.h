#ifndef SNOWFLAKE_PRINT_PROGRAM_H
#define SNOWFLAKE_PRINT_PROGRAM_H
#include <stdbool.h>
#include "core/program.h"
#include "core/instructions.h"

char *get_printable_program(Program *program, bool show_line_number);
char *get_printable_instruction_line(Program *program, InstructionPointer instruction_pointer, char *line_number_format);
char *get_printable_line_number_format(InstructionCount total_lines);
char *get_printable_line_number(char *string_format, InstructionCount current_line);

#endif