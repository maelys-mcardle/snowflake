#ifndef SNOWFLAKE_TYPE_CONVERSION_H
#define SNOWFLAKE_TYPE_CONVERSION_H
#include <stdbool.h>

bool string_to_boolean(char *string, bool *ok);
int string_to_integer(char *string, bool *ok);
float string_to_float(char *string, bool *ok);
bool is_boolean(char *string);
bool is_float(char *string);
bool is_integer(char *string);

#endif