#ifndef SNOWFLAKE_INPUT_H
#define SNOWFLAKE_INPUT_H

#include <stdio.h>
#include <stdbool.h>
#define MAX_INPUT_LENGTH 255

bool get_button(int *string_size, char **string);
bool get_input(int *string_size, char **string);

#endif
