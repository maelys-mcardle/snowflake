#ifndef SNOWFLAKE_ERRORS_H
#define SNOWFLAKE_ERRORS_H

#include <stdio.h>
#include <stdarg.h>

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
#define ERROR_MESG_PARAMETER_MISSING "Instruction %02i is missing parameter #%i\n"
#define ERROR_CODE_FILE_HAD_NO_CODE 7
#define ERROR_MESG_FILE_HAD_NO_CODE "File '%s' contained no Snowflake code.\n"
#define ERROR_CODE_UNRECOGNIZED_ARGUMENT 8
#define ERROR_MESG_UNRECOGNIZED_ARGUMENT "Exiting due to unrecognized argument.\n"
#define ERROR_CODE_NO_ACTION_SELECTED 9
#define ERROR_MESG_NO_ACTION_SELECTED "Did not select an action to perform. Specify --print or --run.\n"
#define ERROR_CODE_LITERAL_IS_NOT_BOOLEAN 10
#define ERROR_MESG_LITERAL_IS_NOT_BOOLEAN "Value '%s' was expected to be a boolean (0 or 1); but it was not.\n"
#define ERROR_CODE_LITERAL_IS_NOT_INTEGER 11
#define ERROR_MESG_LITERAL_IS_NOT_INTEGER "Value '%s' was expected to be an integer; but it was not.\n"
#define ERROR_CODE_LITERAL_IS_NOT_FLOAT 12
#define ERROR_MESG_LITERAL_IS_NOT_FLOAT "Value '%s' was expected to be a float; but it was not.\n"
#define ERROR_CODE_UNRECOGNIZED_INSTRUCTION 13
#define ERROR_MESG_UNRECOGNIZED_INSTRUCTION "Instruction code %02i is not a valid instruction code.\n"
#define ERROR_CODE_UNRECOGNIZED_DEVICE 14
#define ERROR_MESG_UNRECOGNIZED_DEVICE "Device %02i is not a valid device.\n"
#define ERROR_CODE_DEVICE_NOT_SUPPORTED_FOR_OUTPUT 15
#define ERROR_MESG_DEVICE_NOT_SUPPORTED_FOR_OUTPUT "Device %02i does not support output.\n"
#define ERROR_CODE_DEVICE_NOT_SUPPORTED_FOR_INPUT 16
#define ERROR_MESG_DEVICE_NOT_SUPPORTED_FOR_INPUT "Device %02i does not support input.\n"
#define ERROR_CODE_UNEXPECTED_NULL_VALUE 17
#define ERROR_MESG_UNEXPECTED_NULL_VALUE "A value was NULL that should not have been.\n"

#endif
