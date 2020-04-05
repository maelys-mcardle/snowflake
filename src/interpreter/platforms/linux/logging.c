#include <stdbool.h>
#include <stdlib.h>
#include "platforms/logging.h"

/**
 * Global storing the current debug mode.
 */
bool debug_mode = false;

/**
 * Enable the debug mode.
 */
void enable_debug_mode()
{
    debug_mode = true;
}

/**
 * Whether the debug mode is enabled.
 * 
 * @return whether the debug mode is enabled.
 */
bool is_debug_mode()
{
    return debug_mode;
}

/**
 * Insert to the debug log.
 * 
 * @param format printf-compatible format string.
 */
void log_debug(const char * format, ... )
{
    if (debug_mode) {
        va_list args;
        va_start(args, format);
        print_with_va_list(format, args, false);
        va_end(args);
    }
}

/**
 * Insert to the error log.
 * 
 * @param format printf-compatible format string.
 */
void log_error(const char * format, ... )
{
    va_list args;
    va_start (args, format);
    print_with_va_list(format, args, true);
    va_end (args);
}

/**
 * Print to the stdout or stderr
 * 
 * @param format printf-compatible format string.
 * @param args arguments for the string formatter.
 * @param is_error whether to send to stderr instead of stdout.
 */
void print_with_va_list(const char *format, va_list args, bool is_error)
{
    vfprintf(is_error ? stderr : stdout, format, args);
}