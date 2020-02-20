#ifndef SNOWFLAKE_ERRORS_H
#define SNOWFLAKE_ERRORS_H

#include <stdio.h>
#include <stdarg.h>

#define DEBUG_MODE 0
#define SUCCESS 0
#define ERROR_CODE_NO_FILE_SPECIFIED 1
#define ERROR_MESG_NO_FILE_SPECIFIED "Please specify a file to open.\n"
#define ERROR_CODE_COULD_NOT_OPEN_FILE 2
#define ERROR_MESG_COULD_NOT_OPEN_FILE "Could not open file '%s'\n"
#define ERROR_CODE_COULD_NOT_ALLOCATE_MEMORY 3
#define ERROR_MESG_COULD_NOT_ALLOCATE_MEMORY "Could not allocate memory\n"
#define ERROR_CODE_COULD_NOT_PARSE_INTEGER 4
#define ERROR_MESG_COULD_NOT_PARSE_INTEGER "Could not parse '%s' as an integer\n"
#define ERROR_CODE_COULD_NOT_APPEND_INSTRUCTION 5
#define ERROR_MESG_COULD_NOT_APPEND_INSTRUCTION "Could not append the instruction\n"
#define ERROR_CODE_PARAMETER_MISSING 6
#define ERROR_MESG_PARAMETER_MISSING "Parameter #%i missing\n"

void log_error( const char * format, ... );
void log_debug( const char * format, ... );
void print( const char * format, ... );

#endif
