#ifndef SNOWFLAKE_PARSE_FILE_H
#define SNOWFLAKE_PARSE_FILE_H

#include "core/program.h"
#include "core/instructions.h"
#define MAX_LINE_LENGTH 256

int parse_snowflake_file(Program *program, const char *filename);

#endif
