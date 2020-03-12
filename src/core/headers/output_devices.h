#ifndef SNOWFLAKE_OUTPUT_DEVICES_H
#define SNOWFLAKE_OUTPUT_DEVICES_H

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

bool initialize_output();
bool send_to_output(char *string);
bool send_to_random(int seed);

#endif
