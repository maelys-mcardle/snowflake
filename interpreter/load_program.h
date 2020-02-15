#ifndef LOAD_PROGRAM_H
#define LOAD_PROGRAM_H

#include <stdbool.h>
#include "structures.h"
#define COMMENT_SYMBOL ';'

bool load_line_into_program(SnowflakeProgram *program, char *line, int max_line_length);
bool discard_comment(char *line, int max_line_length);

#endif