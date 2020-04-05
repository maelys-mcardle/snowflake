#ifndef SNOWFLAKE_INPUT_DEVICES_H
#define SNOWFLAKE_INPUT_DEVICES_H

#include <stdbool.h>
#define MAX_INPUT_LENGTH 255

bool initialize_input_devices();
bool receive_from_standard_input(char **string, int *string_size);
bool receive_from_button(int *button_code);
bool receive_from_random(int *random_number);

#endif
