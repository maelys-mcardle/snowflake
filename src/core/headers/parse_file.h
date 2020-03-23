#ifndef SNOWFLAKE_PARSE_FILE_H
#define SNOWFLAKE_PARSE_FILE_H

#include "structures/program.h"
#include "structures/instructions.h"
#define MAX_LINE_LENGTH 256

int parse_snowflake_file(Program *program, const char *filename);

#endif
