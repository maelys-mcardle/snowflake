#ifndef SNOWFLAKE_LOGGING_H
#define SNOWFLAKE_LOGGING_H

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

bool initialize_output();
bool send_to_output(char *string);
bool send_to_random(int seed);

void enable_debug_mode();
bool is_debug_mode();

void log_error( const char * format, ... );
void log_debug( const char * format, ... );
void print_with_va_list(const char *format, va_list args, bool is_error);

#endif
