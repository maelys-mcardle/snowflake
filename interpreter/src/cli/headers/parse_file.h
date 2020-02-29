#ifndef SNOWFLAKE_PARSE_FILE_H
#define SNOWFLAKE_PARSE_FILE_H

#include "../../core/headers/program.h"
#include "../../core/headers/instructions.h"
#define MAX_LINE_LENGTH 256

int parse_snowflake_file(Program *program, const char *filename);

#endif
