#ifndef SNOWFLAKE_TYPE_CONVERSION_H
#define SNOWFLAKE_TYPE_CONVERSION_H
#include <stdbool.h>

/**
 * Parses the string as a boolean.
 * String would contain "0" or "1".
 * 
 * @param string string to parse as a boolean.
 * @param ok whether the parsing succeeded.
 * @return the parsed boolean.
 */
bool string_to_boolean(char *string, bool *ok);

/**
 * Parses the string as an integer.
 * 
 * @param string string to parse as an integer.
 * @param ok whether the parsing succeeded.
 * @return the parsed integer.
 */
int string_to_integer(char *string, bool *ok);

/**
 * Parses the string as a float.
 * 
 * @param string string to parse as an float.
 * @param ok whether the parsing succeeded.
 * @return the parsed float.
 */
float string_to_float(char *string, bool *ok);

/**
 * Whether the string can be parsed as a boolean.
 * 
 * @param string string to parse.
 * @return wether the string can be parsed as a boolean.
 */
bool is_boolean(char *string);

/**
 * Whether the string can be parsed as a float.
 * 
 * @param string string to parse.
 * @return wether the string can be parsed as a float.
 */
bool is_float(char *string);

/**
 * Whether the string can be parsed as an integer.
 * 
 * @param string string to parse.
 * @return wether the string can be parsed as an integer.
 */
bool is_integer(char *string);

#endif