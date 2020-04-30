#ifndef SNOWFLAKE_PARSE_FILE_H
#define SNOWFLAKE_PARSE_FILE_H

#include "core/program.h"
#include "core/instructions.h"

// Maximum length of a snowflake line that will be parsed.
#define MAX_LINE_LENGTH 512

/**
 * Process a snowflake file. 
 * 
 * @param program program that's been parsed from the file.
 * @param filename the path to the snowflake file.
 * @return error code.
 */
int parse_snowflake_file(Program *program, const char *filename);

#endif
