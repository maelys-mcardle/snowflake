#ifndef SNOWFLAKE_LOGGING_H
#define SNOWFLAKE_LOGGING_H

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

/**
 * Enable the debug mode.
 */
void enable_debug_mode();

/**
 * Whether the debug mode is enabled.
 * 
 * @return whether the debug mode is enabled.
 */
bool is_debug_mode();

/**
 * Insert to the error log.
 * 
 * @param format printf-compatible format string.
 */
void log_error( const char * format, ... );

/**
 * Insert to the debug log.
 * 
 * @param format printf-compatible format string.
 */
void log_debug( const char * format, ... );

/**
 * Print to the stdout or stderr
 * 
 * @param format printf-compatible format string.
 * @param args arguments for the string formatter.
 * @param is_error whether to send to stderr instead of stdout.
 */
void print_with_va_list(const char *format, va_list args, bool is_error);

#endif
