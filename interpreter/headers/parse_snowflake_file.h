#ifndef SNOWFLAKE_PARSE_SNOWFLAKE_FILE_H
#define SNOWFLAKE_PARSE_SNOWFLAKE_FILE_H

#include <stdbool.h>
#include "structures.h"
#include "instructions.h"
#define MAX_LINE_LENGTH 256
#define CHAR_COMMENT ';'
#define CHAR_NEWLINE '\n'
#define CHAR_SPACE ' '
#define CHAR_TAB '\t'
#define CHAR_END_STRING '\0'

int process_snowflake_file(SnowflakeProgram *program, const char *filename);
bool load_line_into_program(SnowflakeProgram *program, char *line, int max_line_length);
bool discard_comment(char *line, int max_line_length);
int extract_instruction(char *line, int max_line_length, int *instruction);
int extract_parameter(char *line, int max_line_length, int start,
    ParameterType parameter_type, ParameterValue *parameter_value, bool *ok);

int parse_field(char *line, int max_line_length, bool stop_at_whitespace, 
    int start, char *output, int max_output_size);
bool is_whitespace(char character);
bool is_string_end(char character);
int parse_integer(bool *ok, char *string);

#endif