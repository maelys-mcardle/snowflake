#ifndef SNOWFLAKE_OUTPUT_H
#define SNOWFLAKE_OUTPUT_H

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

void enable_debug_mode();
void log_error( const char * format, ... );
void log_debug( const char * format, ... );
void print( const char * format, ... );
void print_with_va_list(const char *format, va_list args, bool is_error);

#endif
