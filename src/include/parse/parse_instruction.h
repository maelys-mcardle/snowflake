#ifndef SNOWFLAKE_PARSE_INSTRUCTION_H
#define SNOWFLAKE_PARSE_INSTRUCTION_H

#include <stdbool.h>
#include "core/program.h"
#include "core/instructions.h"

/**
 * Parses the line, and if its a valid instruction, appends it to the program.
 *
 * @param program program to add instruction to.
 * @param line raw line of code that contains the instruction, once parsed.
 * @param max_line_length the maximum length for the line to parse.
 * @return whether the line of code had an instruction.
 */
bool parse_instruction(Program *program, char *line, int max_line_length);

/** 
 * Loads a line of text into the program.
 * 
 * @param instruction the parsed instruction.
 * @param line raw line of code that contains the instruction, once parsed.
 * @param max_line_length the maximum length for the line to parse.
 * @return true if a line contained an instruction, false if not.
 */
bool parse_instruction_from_line(Instruction *instruction, char *line, int max_line_length);

/** 
 * Extracts the instruction from the line.
 * 
 * @param line the raw line of code containing the instruction.
 * @param max_line_length the maximum size of the raw line of code.
 * @param instruction the parsed instruction code, from the line of code.
 * @param instruction_extracted whether an instruction was extracted from the line of code.
 * @return the last character with the position.
 */
int extract_instruction(char *line, int max_line_length, InstructionCode *instruction, bool *instruction_extracted);

/**
 * Pulls out a parameter from a raw line of code.
 * 
 * @param line the raw line of code.
 * @param max_line_length maximum size the line could be.
 * @param start_position where on the line to start parsing.
 * @param parameter_type expected type of the parameter, based on the instruction.
 * @param parameter_value extracted value of the parameter from the line.
 * @param parameter_missing whether the parameter was missing.
 * @return where on the line the parsing stopped.
 */
int extract_parameter(char *line, int max_line_length, int start,
    ParameterType parameter_type, ParameterValue *parameter_value, 
    bool *parameter_missing);

/** 
 * Extracts non-whitespace text from the line.
 * 
 * @param line the raw line of code.
 * @param max_line_length the maximum size of the line.
 * @param stop_at_whitespace whether the parsing should stop at whitespace, or continue.
 * @param start where in the line to start extracting the field.
 * @param output the extracted text.
 * @param max_output_size the maximum size of the extracted text.
 * @return the last character with the position.
 */
int parse_field(char *line, int max_line_length, bool stop_at_whitespace, 
    int start, char *output, int max_output_size);

#endif