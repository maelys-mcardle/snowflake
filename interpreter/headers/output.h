#ifndef SNOWFLAKE_OUTPUT_H
#define SNOWFLAKE_OUTPUT_H

#include <stdio.h>
#include <stdarg.h>

#define DEBUG_MODE 0
void log_error( const char * format, ... );
void log_debug( const char * format, ... );
void print( const char * format, ... );

#endif
