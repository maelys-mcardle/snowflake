#ifndef SNOWFLAKE_ERRORS_H
#define SNOWFLAKE_ERRORS_H

#include <stdio.h>
#include <stdarg.h>

#define SUCCESS 0
#define ERROR_CODE_NO_FILE_SPECIFIED 1
#define ERROR_MESG_NO_FILE_SPECIFIED "Please specify a file to open. Use --file flag to specify one.\n"
#define ERROR_CODE_COULD_NOT_OPEN_FILE 2
#define ERROR_MESG_COULD_NOT_OPEN_FILE "Could not open file '%s'\n"
#define ERROR_CODE_COULD_NOT_ALLOCATE_MEMORY 3
#define ERROR_MESG_COULD_NOT_ALLOCATE_MEMORY "Could not allocate memory\n"
#define ERROR_CODE_COULD_NOT_PARSE_INTEGER 4
#define ERROR_MESG_COULD_NOT_PARSE_INTEGER "Could not parse '%s' as an integer\n"
#define ERROR_CODE_COULD_NOT_APPEND_INSTRUCTION 5
#define ERROR_MESG_COULD_NOT_APPEND_INSTRUCTION "Could not append the instruction\n"
#define ERROR_CODE_PARAMETER_MISSING 6
#define ERROR_MESG_PARAMETER_MISSING "Instruction %02i is missing parameter #%i\n"
#define ERROR_CODE_FILE_HAD_NO_CODE 7
#define ERROR_MESG_FILE_HAD_NO_CODE "File '%s' contained no Snowflake code.\n"
#define ERROR_CODE_UNRECOGNIZED_ARGUMENT 8
#define ERROR_MESG_UNRECOGNIZED_ARGUMENT "Exiting due to unrecognized argument.\n"
#define ERROR_CODE_NO_ACTION_SELECTED 9
#define ERROR_MESG_NO_ACTION_SELECTED "Did not select an action to perform. Use the --show-code or --run flags.\n"
#endif
