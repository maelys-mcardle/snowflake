#ifndef SNOWFLAKE_PARSE_SNOWFLAKE_LINE_H
#define SNOWFLAKE_PARSE_SNOWFLAKE_LINE_H

#include <stdbool.h>
#include "program.h"
#include "instructions.h"
#define CHAR_COMMENT ';'
#define CHAR_NEWLINE '\n'
#define CHAR_SPACE ' '
#define CHAR_TAB '\t'
#define CHAR_END_STRING '\0'

bool parse_line(Program *program, char *line, int max_line_length);
bool parse_instruction_from_line(Instruction *instruction, char *line, int max_line_length);
bool store_parameter(bool is_literal, char *parameter_string, int max_parameter_size, ParameterValue *parameter_value);
bool discard_comment(char *line, int max_line_length);
int extract_instruction(char *line, int max_line_length, short *instruction);
int extract_parameter(char *line, int max_line_length, int start,
    ParameterType parameter_type, ParameterValue *parameter_value, 
    bool *parameter_missing);
int parse_field(char *line, int max_line_length, bool stop_at_whitespace, 
    int start, char *output, int max_output_size);
bool is_whitespace(char character);
bool is_string_end(char character);
int parse_integer(bool *ok, char *string);
bool strip_end_whitespace(char *string, int max_string_length);

#endif