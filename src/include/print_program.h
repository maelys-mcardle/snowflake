#ifndef SNOWFLAKE_PRINT_PROGRAM_H
#define SNOWFLAKE_PRINT_PROGRAM_H
#include <stdbool.h>
#include "core/program.h"
#include "core/instructions.h"

/** 
 * Gets the entire stringified Snowflake program.
 *
 * @param program the program to print out.
 * @param show_line_number whether to show line numbers.
 * @return the stringified Snowflake program.
 */
char *get_printable_program(Program *program, bool show_line_number);

/**
 * Gets the stringified instruction with optional line number.
 * 
 * @param program the snowflake program.
 * @param instruction_pointer the instruction pointer to get the instruction from.
 * @param line_number_format the format for displaying the line number.
 * @return the stringified instruction.
 */
char *get_printable_instruction_line(Program *program, InstructionPointer instruction_pointer, char *line_number_format);

/**
 * Gets the stringified line number.
 * 
 * @param string_format format for displaying the line number.
 * @param current_line current line index.
 * @return stringified line number.
 */
char *get_printable_line_number(char *string_format, InstructionCount current_line);

/**
 * Gets the format for printing the line number.
 * 
 * It calculates how many leading zeroes to show in the line number,
 * so that the width of the line number is constant throughout displaying
 * all of the program code. So a thousand-line program would have three
 * leading zeroes.
 * 
 * @param total_lines the total number of lines for the program.
 * @return the printf-compatible string format for the line number.
 */
char *get_printable_line_number_format(InstructionCount total_lines);

#endif