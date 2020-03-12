#ifndef SNOWFLAKE_INPUT_DEVICES_H
#define SNOWFLAKE_INPUT_DEVICES_H

#include <stdio.h>
#include <stdbool.h>
#define MAX_INPUT_LENGTH 255

bool initialize_input();
bool receive_from_input(int *string_size, char **string);
bool receive_from_button(int *button_code);
bool receive_from_random(int *random_number);

#endif
