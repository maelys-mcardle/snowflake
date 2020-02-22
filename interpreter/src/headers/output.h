#ifndef SNOWFLAKE_OUTPUT_H
#define SNOWFLAKE_OUTPUT_H

#include <stdio.h>
#include <stdarg.h>

void log_error( const char * format, ... );
void log_debug( const char * format, ... );
void enable_debug_mode();
void print( const char * format, ... );

#endif
