#ifndef SNOWFLAKE_H
#define SNOWFLAKE_H

#include "structures.h"

#define MAX_LINE_LENGTH 256
#define SUCCESS 0
#define ERROR_CODE_NO_FILE_SPECIFIED -1
#define ERROR_MESG_NO_FILE_SPECIFIED "Please specify a file to open.\n"
#define ERROR_CODE_COULD_NOT_OPEN_FILE -2
#define ERROR_MESG_COULD_NOT_OPEN_FILE "Could not open file '%s'\n", filename

int process_snowflake_file(const char *filename);
void initialize_program(SnowflakeProgram *program);
void free_program(SnowflakeProgram *program);

#endif