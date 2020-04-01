#ifndef SNOWFLAKE_PARSE_INSTRUCTION_H
#define SNOWFLAKE_PARSE_INSTRUCTION_H

#include <stdbool.h>
#include "core/program.h"
#include "core/instructions.h"

#define MAX_INSTRUCTION_SIZE 3

bool parse_instruction(Program *program, char *line, int max_line_length);
bool parse_instruction_from_line(Instruction *instruction, char *line, int max_line_length);
bool store_parameter(ParameterType parameter_type, char *parameter_string, int max_parameter_size, ParameterValue *parameter_value);
int extract_instruction(char *line, int max_line_length, InstructionCode *instruction, bool *instruction_extracted);
int extract_parameter(char *line, int max_line_length, int start,
    ParameterType parameter_type, ParameterValue *parameter_value, 
    bool *parameter_missing);
int parse_field(char *line, int max_line_length, bool stop_at_whitespace, 
    int start, char *output, int max_output_size);

#endif